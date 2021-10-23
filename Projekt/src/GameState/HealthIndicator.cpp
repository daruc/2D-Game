#include "HealthIndicator.h"
#include "../Player.h"
#include "../TexturesSingleton.h"


namespace {
	sf::Vector2f POSITION(0.0f, 0.0f);
}

HealthIndicator::HealthIndicator(Player * player)
	: player(player)
{
	TexturesSingleton* textures = TexturesSingleton::getInstance();
	textures->loadHealth();
	sprite.setPosition(POSITION);
}

void HealthIndicator::update(float delta_seconds)
{
	int health = player->getHealth();
	TexturesSingleton* textures = TexturesSingleton::getInstance();
	sprite.setTexture(*textures->getHealth(health));
}

void HealthIndicator::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}