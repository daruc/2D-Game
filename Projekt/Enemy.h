#ifndef ENEMY_H
#define ENEMY_H

#include "AnimatedSprite.h"


class Enemy
{
private:
	enum Anim {
		RIGHT = 0, LEFT = 1, CROUCH_RIGHT = 2, CROUCH_LEFT = 3
	};

	sf::Texture texture;
	AnimatedSprite sprite;

	void configureAnimation();

public:
	Enemy();
	void draw(std::shared_ptr<sf::RenderWindow> window);
	void update();
	void setPosition(sf::Vector2f pos);
};

#endif
