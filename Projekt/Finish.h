#ifndef FINISH_H
#define FINISH_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "Textures.h"


class Finish : public Drawable
{
private:
	Textures textures;
	sf::Sprite sprite;

public:
	Finish();
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
};

#endif