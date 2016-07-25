#include <Box2d/Box2d.h>
#include "Physics.h"
#include "Utils.h"
#include <iostream>

Physics::Physics(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map,
	Player & player)
	: gravity(0.0f, 10.0f), world(gravity), MAX_PLAYER_SPEED(3.0f), player(player)
{
	world.SetContactListener(&myContactListener);
	this->window = window;
	this->map = map;
	myContactListener.setBulletList(&bullet_list);
	myContactListener.setMap(map);
	myContactListener.setWorld(&world);
	myContactListener.setRemoveList(&remove_list);
	loadMap(map);
	loadControlsFromFile();
}

Physics::~Physics()
{
	world.DestroyBody(player_body);
	world.DestroyBody(finish_body);

	while (ground_list.size() > 0)
	{
		b2Body* body = ground_list.back();
		ground_list.pop_back();
		world.DestroyBody(body);
	}

	while (bullet_list.size() > 0)
	{
		b2Body* body = bullet_list.back();
		bullet_list.pop_back();
		world.DestroyBody(body);
	}

	while (enemies_list.size() > 0)
	{
		b2Body* body = enemies_list.back();
		enemies_list.pop_back();
		world.DestroyBody(body);
	}
}

std::pair<b2Vec2*, size_t> Physics::getPoints(std::shared_ptr<sf::ConvexShape> shape)
{
	b2Vec2* points;
	size_t size = shape->getPointCount();
	points = new b2Vec2[size];

	for (size_t i = 0; i < size; ++i)
	{
		sf::Vector2f point = shape->getPoint(i);
		points[i] = b2Vec2(pixels2Meters(point.x), pixels2Meters(point.y));
	}

	return std::pair<b2Vec2*, size_t>(points, size);
}

void Physics::throwBullet(float srcX, float srcY, float dstX, float dstY)
{
	//Creates physics object.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.bullet = true;

	bodyDef.position.Set(pixels2Meters(srcX), pixels2Meters(srcY));
	b2Body* bullet = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.04f / 2, 0.04f / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.isSensor = true;
	b2Fixture* bullet_fixture = bullet->CreateFixture(&fixtureDef);
	bullet_fixture->SetUserData((void *) 10);

	bullet_list.push_back(bullet);

	//Set velocity
	b2Vec2 vec(dstX, dstY);
	float len = vec.Length();
	vec.x /= len;
	vec.y /= len;

	const int BULLET_SPEED = 20;
	vec.x *= BULLET_SPEED;
	vec.y *= BULLET_SPEED;

	std::cout << "v=(" << vec.x << ", " << vec.y << ")\n";
	bullet->SetLinearVelocity(vec);

	//Add bullet to map
	std::shared_ptr<sf::RectangleShape> bulletShape = std::make_shared<sf::RectangleShape>();
	bulletShape->setSize(sf::Vector2f(meters2pixels(0.04f), meters2pixels(0.04f)));
	bulletShape->setPosition(pixels2Meters(srcX), pixels2Meters(srcY));
	map->getBulletsList()->push_back(bulletShape);
}

void Physics::loadMap(std::shared_ptr<Map> map)
{
	//ground
	auto begin = map->getGroundBegin();
	auto end = map->getGroundEnd();

	for (auto it = begin; it != end; ++it)
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(pixels2Meters((*it)->getPosition().x), pixels2Meters((*it)->getPosition().y));
		b2Body* groundBody = world.CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		std::pair<b2Vec2*, size_t> points = getPoints(*it);
		groundBox.Set(points.first, points.second);

		b2Fixture* groundFixture;
		groundFixture = groundBody->CreateFixture(&groundBox, 0.0f);
		groundFixture->SetUserData((void*)(*it)->getType());
		ground_list.push_back(groundBody);

		delete[] points.first;
	}

	//enemies
	auto beginEnemies = map->getEnemiesBegin();
	auto endEnemies = map->getEnemiesEnd();
	for (auto it = beginEnemies; it != endEnemies; ++it)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = true;
		sf::Vector2f position = (*it)->getPosition();

		bodyDef.position.Set(pixels2Meters(position.x + 25), pixels2Meters(position.y + 50));
		b2Body* body = world.CreateBody(&bodyDef);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f / 2, 2.0f / 2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 40.0f;
		fixtureDef.friction = 0.4f;
		fixtureDef.restitution = 0.3f;
		b2Fixture* enemy_fixture = body->CreateFixture(&fixtureDef);
		enemy_fixture->SetUserData((void*)20);

		enemies_list.push_back(body);
	}

	//player
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	sf::Vector2f player = map->getPlayerPosition();

	bodyDef.position.Set(pixels2Meters(player.x), pixels2Meters(player.y));
	player_body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f/2, 2.0f/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 40.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.3f;
	b2Fixture* player_fixture = player_body->CreateFixture(&fixtureDef);

	myContactListener.setPlayerFixture(player_fixture);

	std::cout << "player mass: " << player_body->GetMass();

	//sensor
	b2Fixture* footSensorFixture;
	b2PolygonShape footSensorBox;
	b2FixtureDef footSensorFixtureDef;
	footSensorBox.SetAsBox(0.95f / 2, 0.1f / 2, b2Vec2(0, 2.0f / 2), 0);
	footSensorFixtureDef.isSensor = true;
	footSensorFixtureDef.shape = &footSensorBox;
	footSensorFixture = player_body->CreateFixture(&footSensorFixtureDef);
	footSensorFixture->SetUserData((void*)3);

	//finish
	b2BodyDef finishBodyDef;
	sf::Vector2f finish_position = map->getFinishPosition();
	finishBodyDef.position.Set(pixels2Meters(finish_position.x), pixels2Meters(finish_position.y));
	finish_body = world.CreateBody(&finishBodyDef);
	b2PolygonShape finishBox;
	finishBox.SetAsBox(1.0f / 2, 1.0f / 2);
	b2Fixture* finish_fixture = finish_body->CreateFixture(&finishBox, 0.0);

	myContactListener.setFinishFixture(finish_fixture);

	clock.restart();
}

void Physics::goLeft()
{
	b2Vec2 velocity = player_body->GetLinearVelocity();

	if (velocity.x >= 0)
	{
		player_body->ApplyForce(b2Vec2(-1000.0f, 0.f), player_body->GetWorldCenter(), true);
	}
	else if (velocity.x >= -MAX_PLAYER_SPEED)
	{
		player_body->ApplyForce(b2Vec2(-10000.0f, 0.f), player_body->GetWorldCenter(), true);
	}

	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	if (mouse_pos.x <= window->getSize().x / 2)
	{
		player.goLeft();
	}
	else
	{
		player.goLeftBack();
	}
}

void Physics::goRight()
{
	b2Vec2 velocity = player_body->GetLinearVelocity();
	if (velocity.x <= 0)
	{
		player_body->ApplyForce(b2Vec2(1000.0f, 0.f), player_body->GetWorldCenter(), true);
	}
	else if (velocity.x <= MAX_PLAYER_SPEED)
	{
		player_body->ApplyForce(b2Vec2(10000.0f, 0.f), player_body->GetWorldCenter(), true);
	}

	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);

	if (mouse_pos.x >= window->getSize().x / 2)
	{
		player.goRight();
	}
	else
	{
		player.goRightBack();
	}
}

void Physics::jump()
{
	sf::Time time_since_last_jump = jump_clock.getElapsedTime();
	if (myContactListener.isOnGround() && player_body->GetLinearVelocity().y < MAX_PLAYER_SPEED
		&& time_since_last_jump.asSeconds() > 0.5f)
	{
		jump_clock.restart();
		player_body->ApplyLinearImpulse(b2Vec2(0.0f, -800.0f), b2Vec2(player_body->GetPosition()), true);
	}
		
}

void Physics::controls()
{
	if (sf::Keyboard::isKeyPressed(key_left))
	{
		goLeft();
	}
	else if (sf::Keyboard::isKeyPressed(key_right))
	{
		goRight();

	}
	else if (sf::Keyboard::isKeyPressed(key_jump))
	{
		jump();
	}
	else
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*window);
		if (mouse.x < window->getSize().x/2)
		{
			player.stopLeft();
		}
		else
		{
			player.stopRight();
		}
	}
}

void Physics::simulate()
{
	sf::Time delta_time = clock.getElapsedTime();
	clock.restart();

	//player_body->SetLinearVelocity( b2Vec2(b2Vec2_zero.x, player_body->GetLinearVelocity().y));

	controls();

	//update player_bottom position

	const int positionIt = 3;
	const int velocityIt = 8;
	world.Step(delta_time.asSeconds(), velocityIt, positionIt);

	//remove bodies
	auto begin = remove_list.begin();
	auto end = remove_list.end();

	for (auto it = begin; it != end; ++it)
	{
		world.DestroyBody(*it);
	}
	remove_list.clear();

	b2Vec2 player_position = player_body->GetPosition();
	map->setPlayerPosition(meters2pixels(player_position.x), meters2pixels(player_position.y));

	//update bullets positions
	auto shapesBegin = map->getBulletsList()->begin();
	auto shapesEnd = map->getBulletsList()->end();
	auto bodiesBegin = bullet_list.begin();
	auto bodiesEnd = bullet_list.end();
	
	auto sIt = shapesBegin;
	auto bIt = bodiesBegin;
	while (sIt != shapesEnd)
	{
		sf::Vector2f shapePosition;
		shapePosition.x = meters2pixels((*bIt)->GetPosition().x);
		shapePosition.y = meters2pixels((*bIt)->GetPosition().y);
		(*sIt)->setPosition(shapePosition);

		++sIt;
		++bIt;
	}

	//update enemies positions
	auto beginRect = map->getEnemiesBegin();
	auto endRect = map->getEnemiesEnd();
	auto beginBody = enemies_list.begin();
	auto endBody = enemies_list.end();
	auto rectIt = beginRect;
	auto bodyIt = beginBody;

	while (rectIt != endRect)
	{
		sf::Vector2f rectPosition;
		rectPosition.x = meters2pixels((*bodyIt)->GetPosition().x) - 25;
		rectPosition.y = meters2pixels((*bodyIt)->GetPosition().y) - 50;
		(*rectIt)->setPosition(rectPosition);

		++rectIt;
		++bodyIt;
	}
}

void Physics::loadControlsFromFile()
{
	std::ifstream fin;
	fin.open("controls.bin", std::fstream::binary | std::fstream::in);
	if (!fin.is_open())
	{
		std::cout << "Cannot load controls.bin file.\n";
	}

	int key;
	char * buffer = new char[16];
	fin.read(buffer, 16);
	memcpy(&key, buffer, 4);
	key_left = static_cast<sf::Keyboard::Key>(key);
	memcpy(&key, buffer + 4, 4);
	key_right = static_cast<sf::Keyboard::Key>(key);
	memcpy(&key, buffer + 8, 4);
	key_crouch = static_cast<sf::Keyboard::Key>(key);
	memcpy(&key, buffer + 12, 4);
	key_jump = static_cast<sf::Keyboard::Key>(key);

	delete[] buffer;
	fin.close();
}