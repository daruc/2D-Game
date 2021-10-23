#ifndef GUI_CONSTANTS_H
#define GUI_CONSTANTS_H

#include <SFML/Graphics.hpp>

namespace GUIConstants
{
	const sf::Color LABEL_TEXT_COLOR = sf::Color::White;
	const unsigned int BUTTON_TEXT_SIZE = 25;
	const sf::Color BUTTON_TEXT_COLOR = sf::Color::Black;
	const sf::Color BUTTON_IDLE_COLOR(200, 200, 200, 255);
	const sf::Color BUTTON_PRESSED_COLOR = sf::Color::Red;
	const sf::Color BUTTON_FOCUSED_COLOR = sf::Color::Yellow;
	const sf::Color HEADER_COLOR(0, 0, 80, 255);
	const float HEADER_HEIGHT = 80.0f;
	const sf::Color BACKGROUND_COLOR(0, 0, 100, 255);
}

#endif