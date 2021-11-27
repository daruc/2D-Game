#include <iostream>

#include <box2d/box2d.h>
#include <box2d/b2_fixture.h>

#include "Physics.h"
#include "Utils/Utils.h"
#include "Enemy.h"
#include "Map.h"
#include "Bullet.h"
#include "FixtureId.h"


Physics::Physics(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: gravity(0.0f, 10.0f), world(gravity)
{
	world.SetContactListener(&myContactListener);
	this->window = window;
	this->map = map;
	myContactListener.setMap(map);
	myContactListener.setWorld(&world);
	myContactListener.setRemoveList(&remove_list);
	loadMap(map);
}

Physics::~Physics()
{

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
		(*it)->initFixture(&world);
	}

	for (std::shared_ptr<Enemy> enemy : *map->getEnenemiesList())
	{
		enemy->initFixture(&world, map);
	}

	map->getPlayer()->initFixture(&world, map);
	map->getFinish()->initFixture(&world, map);

	clock.restart();
}


void Physics::simulate()
{
	sf::Time delta_time = clock.getElapsedTime();
	clock.restart();

	//update player_bottom position
	const int positionIt = 3;
	const int velocityIt = 8;
	world.Step(delta_time.asSeconds(), velocityIt, positionIt);
}
