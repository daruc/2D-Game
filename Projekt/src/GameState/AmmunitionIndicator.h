#ifndef AMMUNITION_INDICATOR_H
#define AMMUNITION_INDICATOR_H

#include <SFML/Graphics.hpp>

#include "../Drawable.h"
#include "../Updatable.h"


class Player;


class AmmunitionIndicator : public Drawable, public Updatable
{
private:
	Player * player;
	sf::Sprite sprite;
	sf::Text text;

public:
	AmmunitionIndicator(std::shared_ptr<sf::RenderWindow> window, Player * player);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float delta_seconds) override;
};

#endif // !AMMUNITION_INDICATOR_H
