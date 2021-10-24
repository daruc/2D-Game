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

	b2Body* player_body;
	b2Body* finish_body;
	std::list<b2Body*> ground_list;
	std::list<b2Body*> enemies_list;
	std::list<b2Body*> bullet_list;
	std::list<b2Body*> remove_list;

	float max_player_speed;

	void loadMap(std::shared_ptr<Map> map);

	void loadControlsFromFile();
	sf::Keyboard::Key key_left;
	sf::Keyboard::Key key_right;
	sf::Keyboard::Key key_jump;
	sf::Keyboard::Key key_crouch;

	std::pair<b2Vec2*, size_t> getPoints(std::shared_ptr<sf::ConvexShape> shape);
	void goLeft();
	void goRight();
	void jump();
	void controls();

public:
	Physics(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	Physics::~Physics();
	void simulate();

	inline bool isWin() const { return myContactListener.isWin(); }
	inline bool isDead() const { return myContactListener.isDead(); }

	inline void setKnockSound(sf::Sound* knock_sound)
	{
		myContactListener.setKnockSound(knock_sound);
	}

	void throwBullet(sf::Vector2f source, sf::Vector2f direction);
};

#endif