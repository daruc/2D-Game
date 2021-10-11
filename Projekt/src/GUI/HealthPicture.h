#ifndef HEALTH_PICTURE_H
#define HEALTH_PICTURE_H

#include "../Drawable.h"
#include "../Updatable.h"
#include "../Textures.h"
#include <SFML/Graphics.hpp>


class Player;

class HealthPicture : public Drawable, public Updatable
{
private:
	Player * player;
	sf::Sprite sprite;
	Textures textures;

public:
	HealthPicture(Player * player);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float delta_seconds) override;
};

#endif