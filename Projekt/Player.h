#ifndef PLAYER_H
#define PLAYER_H
#include "AnimatedSprite.h"
class Player
{
private:
	enum Anim {
		RIGHT = 0, LEFT = 1
	};

	AnimatedSprite sprite;
	sf::Sprite pistol;
	sf::Texture texture;
	sf::Texture texture_pistol;
	unsigned int bullets;
	const unsigned int max_bullets;

	void configureAnimations();
public:
	Player();
	void update(std::shared_ptr<sf::RenderWindow> window);
	void draw(std::shared_ptr<sf::RenderWindow> window);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	void goLeft();
	void goRight();
	void stopLeft();
	void stopRight();
	void goLeftBack();
	void goRightBack();
};

#endif
