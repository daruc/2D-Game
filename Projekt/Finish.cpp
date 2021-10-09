#include "Finish.h"
#include "Utils.h"


Finish::Finish()
{
	textures.loadFinish();

	sprite.setTexture(*textures.getFinish(), true);
	int width = meters2pixels(1.0f);
	int height = meters2pixels(1.0f);
	sprite.setOrigin(sf::Vector2f(width / 2, height / 2));
}

void Finish::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

void Finish::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

sf::Vector2f Finish::getPosition() const
{
	return sprite.getPosition();
}