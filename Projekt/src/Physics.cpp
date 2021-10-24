#include <iostream>

#include <box2d/box2d.h>
#include <box2d/b2_fixture.h>

#include "Physics.h"
#include "Utils/Utils.h"
#include "Enemy.h"
#include "Map.h"
#include "Bullet.h"


Physics::Physics(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: gravity(0.0f, 10.0f), world(gravity)
{
	max_player_speed = 3.0f;
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

void Physics::throwBullet(sf::Vector2f source, sf::Vector2f direction)
{
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(&world, source, direction);
	map->getBulletsList()->push_back(bullet);
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
		groundBodyDef.userData.pointer = (*it)->getType();
		b2Body* groundBody = world.CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		std::pair<b2Vec2*, size_t> points = getPoints(*it);
		groundBox.Set(points.first, points.second);

		b2Fixture* groundFixture;
		groundFixture = groundBody->CreateFixture(&groundBox, 0.0f);
		ground_list.push_back(groundBody);

		delete[] points.first;
	}

	for (std::shared_ptr<Enemy> enemy : *map->getEnenemiesList())
	{
		enemy->initFixture(&world, map);
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
	fixtureDef.userData.pointer = 11;
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
	footSensorFixtureDef.userData.pointer = 3;
	footSensorFixture = player_body->CreateFixture(&footSensorFixtureDef);

	//finish
	b2BodyDef finishBodyDef;
	sf::Vector2f finish_position = map->getFinishPosition();
	finishBodyDef.position.Set(pixels2Meters(finish_position.x), pixels2Meters(finish_position.y));
	finish_body = world.CreateBody(&finishBodyDef);
	b2PolygonShape finishBox;
	finishBox.SetAsBox(1.0f / 2, 1.0f / 2);

	b2FixtureDef finishSensorFixtureDef;
	finishSensorFixtureDef.shape = &finishBox;
	finishSensorFixtureDef.isSensor = true;
	b2Fixture* finish_fixture = finish_body->CreateFixture(&finishSensorFixtureDef);

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
	else if (velocity.x >= -max_player_speed)
	{
		player_body->ApplyForce(b2Vec2(-10000.0f, 0.f), player_body->GetWorldCenter(), true);
	}

	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	if (mouse_pos.x <= window->getSize().x / 2)
	{
		if (map->getPlayer()->getCrouch() == false)
		{
			map->getPlayer()->goLeft();
		}
		else
		{
			map->getPlayer()->goCrouchLeft();
		}
	}
	else
	{
		if (map->getPlayer()->getCrouch() == false)
		{
			map->getPlayer()->goLeftBack();
		}
		else
		{
			map->getPlayer()->goCrouchLeftBack();
		}
	}
}

void Physics::goRight()
{
	b2Vec2 velocity = player_body->GetLinearVelocity();
	if (velocity.x <= 0)
	{
		player_body->ApplyForce(b2Vec2(1000.0f, 0.f), player_body->GetWorldCenter(), true);
	}
	else if (velocity.x <= max_player_speed)
	{
		player_body->ApplyForce(b2Vec2(10000.0f, 0.f), player_body->GetWorldCenter(), true);
	}

	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);

	if (mouse_pos.x >= window->getSize().x / 2)
	{
		if (map->getPlayer()->getCrouch() == false)
		{
			map->getPlayer()->goRight();
		}
		else
		{
			map->getPlayer()->goCrouchRight();
		}
	}
	else
	{
		if (map->getPlayer()->getCrouch() == false)
		{
			map->getPlayer()->goRightBack();
		}
		else
		{
			map->getPlayer()->goCrouchRightBack();
		}
	}
}

void Physics::jump()
{
	sf::Time time_since_last_jump = jump_clock.getElapsedTime();
	if (myContactListener.isOnGround() && player_body->GetLinearVelocity().y < max_player_speed
		&& time_since_last_jump.asSeconds() > 0.5f)
	{
		jump_clock.restart();
		player_body->ApplyLinearImpulse(b2Vec2(0.0f, -800.0f), b2Vec2(player_body->GetPosition()), true);
	}
		
}

void Physics::controls()
{
	bool rest = true;
	if (sf::Keyboard::isKeyPressed(key_left))
	{
		goLeft();
		rest = false;
	}
	if (sf::Keyboard::isKeyPressed(key_right))
	{
		goRight();
		rest = false;

	}
	if (sf::Keyboard::isKeyPressed(key_jump))
	{
		jump();
		rest = false;
	}
	if (sf::Keyboard::isKeyPressed(key_crouch))
	{
		if (map->getPlayer()->getCrouch() == false)
		{
			std::cout << "set crouch\n";
			map->getPlayer()->setCrouch(true);
			max_player_speed = 1.5;

			b2Fixture* oldFixture = player_body->GetFixtureList();
			if (oldFixture->IsSensor())
			{
				oldFixture = oldFixture->GetNext();
			}
			player_body->DestroyFixture(oldFixture);

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(1.0f / 2, 1.0f / 2);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 80.0f;
			fixtureDef.friction = 0.4f;
			fixtureDef.restitution = 0.3f;
			b2Fixture* player_fixture = player_body->CreateFixture(&fixtureDef);

			myContactListener.setPlayerFixture(player_fixture);
		}
		
	}
	else
	{
		if (map->getPlayer()->getCrouch() == true)
		{
			std::cout << "set crouch false\n";
			map->getPlayer()->setCrouch(false);
			max_player_speed = 3.0;

			b2Fixture* oldFixture = player_body->GetFixtureList();
			if (oldFixture->IsSensor())
			{
				oldFixture = oldFixture->GetNext();
			}
			player_body->DestroyFixture(oldFixture);

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(1.0f / 2, 2.0f / 2);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 40.0f;
			fixtureDef.friction = 0.4f;
			fixtureDef.restitution = 0.3f;
			b2Fixture* player_fixture = player_body->CreateFixture(&fixtureDef);

			myContactListener.setPlayerFixture(player_fixture);
		}
	}
	if (rest)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*window);
		if (mouse.x < window->getSize().x/2)
		{
			if (map->getPlayer()->getCrouch() == false)
			{
				map->getPlayer()->stopLeft();
			}
			else
			{
				map->getPlayer()->stopCrouchLeft();
			}
		}
		else
		{
			if (map->getPlayer()->getCrouch() == false)
			{
				map->getPlayer()->stopRight();
			}
			else
			{
				map->getPlayer()->stopCrouchRight();
			}
		}
	}
}

void Physics::simulate()
{
	sf::Time delta_time = clock.getElapsedTime();
	clock.restart();

	controls();

	//update player_bottom position
	const int positionIt = 3;
	const int velocityIt = 8;
	world.Step(delta_time.asSeconds(), velocityIt, positionIt);

	b2Vec2 player_position = player_body->GetPosition();
	map->setPlayerPosition(meters2pixels(player_position.x), meters2pixels(player_position.y));
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