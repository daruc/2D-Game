#ifndef PHYSICS_H
#define PHYSICS_H

#include <list>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Map.h"
#include "MyContactListener.h"


class Physics
{
private:
	sf::Clock clock;
	sf::Clock jump_clock;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Map> map;
	b2Vec2 gravity;
	b2World world;
	MyContactListener myContactListener;

	b2Body* finish_body;
	std::list<b2Body*> ground_list;
	std::list<b2Body*> remove_list;

	void loadMap(std::shared_ptr<Map> map);

	std::pair<b2Vec2*, size_t> getPoints(std::shared_ptr<sf::ConvexShape> shape);

public:
	Physics(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	Physics::~Physics();
	void simulate();

	inline void setKnockSound(sf::Sound* knock_sound)
	{
		myContactListener.setKnockSound(knock_sound);
	}

	void throwBullet(sf::Vector2f source, sf::Vector2f direction);
};

#endif