#include <iostream>
#include <SFML/Window.hpp>
#include <cctype>
#include "TextField.h"
#include "Control.h"

TextField::TextField(std::shared_ptr <sf::RenderWindow> window)
	: Control(window)
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	text.setFont(font);
	text.setString("");
	text.setCharacterSize(25);
	text.setColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color::White);
	rectangle.setOutlineThickness(2.0f);
	rectangle.setOutlineColor(sf::Color::Black);
	focus = false;
}

void TextField::handleKeys(sf::Event & event)
{
	char ch = '#';
	switch (event.key.code)
	{
	case sf::Keyboard::A:
		ch = 'a';
		break;
	case sf::Keyboard::B:
		ch = 'b';
		break;
	case sf::Keyboard::C:
		ch = 'c';
		break;
	case sf::Keyboard::D:
		ch = 'd';
		break;
	case sf::Keyboard::E:
		ch = 'e';
		break;
	case sf::Keyboard::F:
		ch = 'f';
		break;
	case sf::Keyboard::G:
		ch = 'g';
		break;
	case sf::Keyboard::H:
		ch = 'h';
		break;
	case sf::Keyboard::I:
		ch = 'i';
		break;
	case sf::Keyboard::J:
		ch = 'j';
		break;
	case sf::Keyboard::K:
		ch = 'k';
		break;
	case sf::Keyboard::L:
		ch = 'l';
		break;
	case sf::Keyboard::M:
		ch = 'm';
		break;
	case sf::Keyboard::N:
		ch = 'n';
		break;
	case sf::Keyboard::O:
		ch = 'o';
		break;
	case sf::Keyboard::P:
		ch = 'p';
		break;
	case sf::Keyboard::Q:
		ch = 'q';
		break;
	case sf::Keyboard::R:
		ch = 'r';
		break;
	case sf::Keyboard::S:
		ch = 's';
		break;
	case sf::Keyboard::T:
		ch = 't';
		break;
	case sf::Keyboard::U:
		ch = 'u';
		break;
	case sf::Keyboard::V:
		ch = 'v';
		break;
	case sf::Keyboard::W:
		ch = 'w';
		break;
	case sf::Keyboard::X:
		ch = 'x';
		break;
	case sf::Keyboard::Y:
		ch = 'y';
		break;
	case sf::Keyboard::Z:
		ch = 'z';
		break;
	case sf::Keyboard::Num0:
	case sf::Keyboard::Numpad0:
		ch = '0';
		break;
	case sf::Keyboard::Num1:
	case sf::Keyboard::Numpad1:
			ch = '1';
		break;
	case sf::Keyboard::Num2:
	case sf::Keyboard::Numpad2:
		ch = '2';
		break;
	case sf::Keyboard::Num3:
	case sf::Keyboard::Numpad3:
		ch = '3';
		break;
	case sf::Keyboard::Num4:
	case sf::Keyboard::Numpad4:
		ch = '4';
		break;
	case sf::Keyboard::Num5:
	case sf::Keyboard::Numpad5:
		ch = '5';
		break;
	case sf::Keyboard::Num6:
	case sf::Keyboard::Numpad6:
		ch = '6';
		break;
	case sf::Keyboard::Num7:
	case sf::Keyboard::Numpad7:
		ch = '7';
		break;
	case sf::Keyboard::Num8:
	case sf::Keyboard::Numpad8:
		ch = '8';
		break;
	case sf::Keyboard::Num9:
	case sf::Keyboard::Numpad9:
		ch = '9';
		break;
	case sf::Keyboard::Space:
		ch = ' ';
		break;
	case sf::Keyboard::BackSpace:
		sf::String str = text.getString();
		str = str.substring(0, str.getSize() - 1);
		text.setString(str);
		break;
	}

	if (ch != '#')
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			if (isalpha(ch)) ch = toupper(ch);
		}

		std::cout << ch << std::endl;
		sf::String str = text.getString();
		str += ch;
		text.setString(str);
	}
	
}

void TextField::handleEvents(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i coor(sf::Mouse::getPosition(*window));
		sf::Vector2f dim(rectangle.getSize());
		sf::Vector2f rec_coor(rectangle.getPosition());

		if (coor.x >= rec_coor.x && coor.x <= rec_coor.x + dim.x
			&& coor.y >= rec_coor.y && coor.y <= rec_coor.y + dim.y)
		{
			focus = true;
			rectangle.setOutlineColor(sf::Color::Yellow);
		}
		else
		{
			focus = false;
			rectangle.setOutlineColor(sf::Color::Black);
		}
	}
	else if (focus && event.type == sf::Event::KeyPressed)
	{
		handleKeys(event);
	}
}

void TextField::update()
{

}

void TextField::draw()
{
	window->draw(rectangle);
	window->draw(text);
}

void TextField::setDimensions(float width, float height)
{
	rectangle.setSize(sf::Vector2f(width, height));
}

void TextField::setCoordinates(float x, float y)
{
	rectangle.setPosition(sf::Vector2f(x, y));
	text.setPosition(sf::Vector2f(x, y));
}