#ifndef PLAYER_H
#define PLAYER_H
#include "AnimatedSprite.h"
class Player
{
private:
	enum Anim {
		RIGHT = 0, LEFT = 1, CROUCH_RIGHT = 2, CROUCH_LEFT = 3
	};

	AnimatedSprite sprite;
	sf::Sprite pistol;
	sf::Texture texture;
	sf::Texture texture_pistol;
	unsigned int bullets;
	unsigned int health;
	const unsigned int max_bullets;
	bool crouch;

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

	void goCrouchLeft();
	void goCrouchRight();
	void stopCrouchLeft();
	void stopCrouchRight();
	void goCrouchLeftBack();
	void goCrouchRightBack();

	bool shoot();

	inline int getHealth() { return health; }
	inline int getBullets() { return bullets; }
	void setCrouch(bool crouch);
	inline bool getCrouch() { return crouch; }
	bool reload();
};

#endif
