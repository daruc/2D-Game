#ifndef PHYSICS_H
#define PHYSICS_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <list>
#include "Map.h"

class Physics
{
private:
	sf::Clock clock;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Map> map;
	b2Vec2 gravity;
	b2World world;

	b2Body* player_body;
	std::list<b2Body*> ground_list;

	const float MAX_PLAYER_SPEED;

	void loadMap(std::shared_ptr<Map> map);
	std::pair<b2Vec2*, size_t> getPoints(std::shared_ptr<sf::ConvexShape> shape);

	bool ready;
public:
	Physics(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	Physics::~Physics();
	void simulate();
};

#endif