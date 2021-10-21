#ifndef ENEMY_H
#define ENEMY_H

#include "AnimatedSprite.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Binary.h"


class Enemy : public Updatable, public Drawable, public Binary
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
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float delta_seconds) override;
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const;

	std::vector<char> toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;
};

#endif
