#include "HealthPicture.h"
#include "../Player.h"


HealthPicture::HealthPicture(Player * player)
	: player(player)
{
	textures.loadHealth();
	sprite.setPosition(0.0f, 0.0f);
}

void HealthPicture::update(float delta_seconds)
{
	int h = player->getHealth();
	sprite.setTexture(*textures.getHealth(h));
}

void HealthPicture::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}