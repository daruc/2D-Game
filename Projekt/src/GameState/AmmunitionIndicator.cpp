#include <sstream>

#include "AmmunitionIndicator.h"
#include "../Player.h"


namespace
{
	const float TEXT_POSITION_X_RIGHT_OFFSET = 70.0f;
	const float TEXT_POSITION_Y_TOP_OFFSET = 8.0f;
	const int FONT_SIZE = 17;
	const char* FONT_FILE_NAME = "font.ttf";
}

AmmunitionIndicator::AmmunitionIndicator(std::shared_ptr<sf::RenderWindow> window, Player * player)
	: player(player)
{
	font.loadFromFile(FONT_FILE_NAME);
	text.setFont(font);
	float resolutionX = window->getSize().x;
	text.setPosition(resolutionX - TEXT_POSITION_X_RIGHT_OFFSET, TEXT_POSITION_Y_TOP_OFFSET);
	text.setCharacterSize(FONT_SIZE);

	textures.loadGunGui();
	sprite.setTexture(*textures.getGunGui());

	sprite.setPosition(resolutionX - sprite.getLocalBounds().width, TEXT_POSITION_Y_TOP_OFFSET);
}

void AmmunitionIndicator::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
	window->draw(text);
}

void AmmunitionIndicator::update(float delta_seconds)
{
	int bullets = player->getBullets();
	std::stringstream sstream;
	sstream << bullets;
	text.setString(sstream.str());
}