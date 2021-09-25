#include <SFML/Window.hpp>
#include <iostream>
#include "Button.h"


Button::Button(std::shared_ptr<sf::RenderWindow> window, std::string title)
	: Control(window)
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	text.setFont(font);
	text.setString(title);
	text.setCharacterSize(25);
	text.setColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color(200, 200, 200, 255));
}

Button::Button(std::shared_ptr<sf::RenderWindow> window, std::wstring title)
	: Control(window)
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	text.setFont(font);
	text.setString(title);
	text.setCharacterSize(25);
	text.setColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color(200, 200, 200, 255));
}

void Button::handleEvents(sf::Event & event)
{
	
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i coor(sf::Mouse::getPosition(*window));
		sf::Vector2f dim(rectangle.getSize());
		sf::Vector2f rec_coor(rectangle.getPosition());

		if (coor.x >= rec_coor.x && coor.x <= rec_coor.x + dim.x
			&& coor.y >= rec_coor.y && coor.y <= rec_coor.y + dim.y)
		{
			listener(text.getString());
		}
	}
}

void Button::update(float deltaSeconds)
{
	sf::Vector2i coor(sf::Mouse::getPosition(*window));
	sf::Vector2f dim(rectangle.getSize());
	sf::Vector2f rec_coor(rectangle.getPosition());

	if (coor.x >= rec_coor.x && coor.x <= rec_coor.x + dim.x
		&& coor.y >= rec_coor.y && coor.y <= rec_coor.y + dim.y)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (!click)
			{
				rectangle.setFillColor(sf::Color::Red);
				click = true;
			}
		}
		else
		{
			click = false;
			rectangle.setFillColor(sf::Color::Yellow);
		}
	}
	else
	{
		click = false;
		rectangle.setFillColor(sf::Color(200, 200, 200, 255));
	}
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
	text_position.x = (int) (rect_position.x + (rect_dim.width - text_dim.width) / 2.0f);
	text_position.y = (int) (rect_position.y + (rect_dim.height - text_dim.height) / 2.0f - 5.0f);
	text.setPosition(text_position);
}

void Button::setDimensions(float width, float height)
{
	rectangle.setSize(sf::Vector2f(width, height));
	setTextPosition();
}

void Button::setCoordinates(float x, float y)
{
	rectangle.setPosition(sf::Vector2f(x, y));
	setTextPosition();
}