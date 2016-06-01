#include <Box2d/Box2d.h>
#include "Physics.h"
#include "Utils.h"
#include <iostream>

Physics::Physics(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: gravity(0.0f, 10.0f), world(gravity), MAX_PLAYER_SPEED(3.0f)
{
	this->window = window;
	this->map = map;
	ready = false;
	loadMap(map);
}

Physics::~Physics()
{
	world.DestroyBody(player_body);

	while (ground_list.size() > 0)
	{
		b2Body* body = ground_list.back();
		ground_list.pop_back();
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

void Physics::loadMap(std::shared_ptr<Map> map)
{
	//ground
	auto begin = map->getGroundBegin();
	auto end = map->getGroundEnd();

	for (auto it = begin; it != end; ++it)
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, 0.0f);
		b2Body* groundBody = world.CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		std::pair<b2Vec2*, size_t> points = getPoints(*it);
		groundBox.Set(points.first, points.second);
		groundBody->CreateFixture(&groundBox, 0.0f);
		ground_list.push_back(groundBody);

		delete[] points.first;
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
	fixtureDef.friction = 0.9f;
	fixtureDef.restitution = 0.3f;
	player_body->CreateFixture(&fixtureDef);

	std::cout << "player mass: " << player_body->GetMass();

	ready = true;
	clock.restart();
}

void Physics::simulate()
{
	if (ready)
	{
		sf::Time delta_time = clock.getElapsedTime();
		clock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			b2Vec2 velocity = player_body->GetLinearVelocity();
			if (velocity.x >= -MAX_PLAYER_SPEED)
			{
				velocity.x = -MAX_PLAYER_SPEED;
				player_body->SetLinearVelocity(velocity);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			b2Vec2 velocity = player_body->GetLinearVelocity();
			if (velocity.x <= MAX_PLAYER_SPEED)
			{
				velocity.x = MAX_PLAYER_SPEED;
				player_body->SetLinearVelocity(velocity);
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			player_body->ApplyLinearImpulse(b2Vec2(0.0f, -5.0f), b2Vec2(player_body->GetPosition()), true);
		}

		const int positionIt = 3;
		const int velocityIt = 8;
		world.Step(delta_time.asSeconds(), velocityIt, positionIt);

		b2Vec2 player_position = player_body->GetPosition();
		map->setPlayerPosition(meters2pixels(player_position.x), meters2pixels(player_position.y));
		/*std::cout << "player("
			<< player_body->GetPosition().x << ", " << player_body->GetPosition().y << ")\n";*/
	}
}