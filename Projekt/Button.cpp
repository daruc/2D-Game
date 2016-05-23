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
	text.setColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color(200, 200, 200, 255));
}

void Button::update()
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
				listener(text.getString());
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

void Button::draw()
{
	window->draw(rectangle);
	window->draw(text);
}

void Button::setDimensions(float width, float height)
{
	rectangle.setSize(sf::Vector2f(width, height));
}

void Button::setCoordinates(float x, float y)
{
	rectangle.setPosition(sf::Vector2f(x, y));
	text.setPosition(sf::Vector2f(x, y));
}