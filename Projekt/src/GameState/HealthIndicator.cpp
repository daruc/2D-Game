#include "HealthIndicator.h"
#include "../Player.h"


namespace {
	sf::Vector2f POSITION(0.0f, 0.0f);
}

HealthIndicator::HealthIndicator(Player * player)
	: player(player)
{
	textures.loadHealth();
	sprite.setPosition(POSITION);
}

void HealthIndicator::update(float delta_seconds)
{
	int health = player->getHealth();
	sprite.setTexture(*textures.getHealth(health));
}

void HealthIndicator::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}