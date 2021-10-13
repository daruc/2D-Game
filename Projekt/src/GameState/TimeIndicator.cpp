#include <sstream>

#include "TimeIndicator.h"

namespace
{
	const char* FONT_FILE_NAME = "font.ttf";
	const float FONT_SIZE = 17.0f;
	const float TEXT_POSITION_TOP_OFFSET = 8.0f;
	const sf::Vector2f SPRITE_POSITION_OFFSET(-37.0f, -8.0f);
	const int FLOAT_PRECISION = 1;
}

TimeIndicator::TimeIndicator(std::shared_ptr<sf::RenderWindow> window)
	: elapsed_seconds(0.0f)
{
	font.loadFromFile(FONT_FILE_NAME);
	text.setFont(font);

	text.setCharacterSize(FONT_SIZE);
	float horizontalCenter = window->getSize().x / 2.0f;
	text.setPosition(horizontalCenter, TEXT_POSITION_TOP_OFFSET);

	textures.loadClock();
	sprite.setTexture(*textures.getClock());
	sf::Vector2f clock_pos = text.getPosition() + SPRITE_POSITION_OFFSET;
	sprite.setPosition(clock_pos);
}

void TimeIndicator::update(float delta_seconds)
{
	elapsed_seconds += delta_seconds;

	std::stringstream stream;
	stream.precision(FLOAT_PRECISION);
	stream << std::fixed << elapsed_seconds;
	text.setString(stream.str());
}

void TimeIndicator::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
	window->draw(text);
}

float TimeIndicator::getElapsedSeconds() const
{
	return elapsed_seconds;
}