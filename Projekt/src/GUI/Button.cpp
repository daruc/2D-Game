#include <iostream>

#include <SFML/Window.hpp>

#include "Button.h"
#include "../FontSingleton.h"
#include "GUIConstants.h"


Button::Button(std::shared_ptr<sf::RenderWindow> window, std::string title)
	: Control(window)
{
	initButton(title);
}

void Button::initButton(sf::String title)
{
	initText(title);
	initBackground();
}

const sf::Font& Button::getFont() const
{
	return FontSingleton::getInstance()->getFont();
}

void Button::initText(sf::String title)
{
	text.setFont(getFont());
	text.setString(title);
	text.setCharacterSize(GUIConstants::BUTTON_TEXT_SIZE);
	text.setColor(GUIConstants::BUTTON_TEXT_COLOR);
}

void Button::initBackground()
{
	rectangle.setFillColor(GUIConstants::BUTTON_IDLE_COLOR);
}

Button::Button(std::shared_ptr<sf::RenderWindow> window, std::wstring title)
	: Control(window)
{
	initButton(title);
}

void Button::handleEvents(sf::Event & event)
{
	if (isMouseButtonReleasedInsideButton(event))
	{
		listener(text.getString());
	}
}

bool Button::isMouseButtonReleasedInsideButton(sf::Event & event)
{
	return isMouseButtonReleased(event) && isMouseInsideButton();
}

bool Button::isMouseButtonReleased(sf::Event& event)
{
	return event.type == sf::Event::MouseButtonReleased;
}

bool Button::isMouseInsideButton()
{
	sf::Vector2i coor(sf::Mouse::getPosition(*window));
	sf::Vector2f dim(rectangle.getSize());
	sf::Vector2f rec_coor(rectangle.getPosition());

	return (coor.x >= rec_coor.x && coor.x <= rec_coor.x + dim.x
		&& coor.y >= rec_coor.y && coor.y <= rec_coor.y + dim.y);
}

void Button::update(float delta_seconds)
{
	sf::Vector2i coor(sf::Mouse::getPosition(*window));
	sf::Vector2f dim(rectangle.getSize());
	sf::Vector2f rec_coor(rectangle.getPosition());

	if (isMouseInsideButton())
	{
		if (isLeftMouseButtonPressed())
		{
			setPressed();
		}
		else
		{
			setFocused();
		}
	}
	else
	{
		setIdle();
	}
}

bool Button::isLeftMouseButtonPressed()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Button::setPressed()
{
	rectangle.setFillColor(GUIConstants::BUTTON_PRESSED_COLOR);
}

void Button::setFocused()
{
	rectangle.setFillColor(GUIConstants::BUTTON_FOCUSED_COLOR);
}

void Button::setIdle()
{
	rectangle.setFillColor(GUIConstants::BUTTON_IDLE_COLOR);
}

void Button::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(rectangle);
	window->draw(text);
}

void Button::setTextPosition()
{
	sf::FloatRect text_dim = text.getLocalBounds();
	sf::FloatRect rect_dim = rectangle.getLocalBounds();
	sf::Vector2f rect_position = rectangle.getPosition();
	sf::Vector2f text_position;
	text_position.x = static_cast<int>(rect_position.x + (rect_dim.width - text_dim.width) / 2.0f);
	text_position.y = static_cast<int>(rect_position.y + (rect_dim.height - text_dim.height) / 2.0f - 5.0f);
	text.setPosition(text_position);
}


void Button::setDimensions(sf::Vector2f dimensions)
{
	rectangle.setSize(dimensions);
	setTextPosition();
}

void Button::setPosition(sf::Vector2f position)
{
	rectangle.setPosition(position);
	setTextPosition();
}

sf::Vector2f Button::getDimensions() const
{
	return rectangle.getSize();
}

sf::Vector2f Button::getCoordinates() const
{
	return rectangle.getPosition();
}