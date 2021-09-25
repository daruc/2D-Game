#include <iostream>
#include "KeyField.h"

KeyField::KeyField(std::shared_ptr<sf::RenderWindow> window)
	: Control(window)
{
	rectangle.setFillColor(sf::Color::White);
	rectangle.setOutlineThickness(3.0f);
	rectangle.setOutlineColor(sf::Color::Black);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	text.setFont(font);
	text.setCharacterSize(25);
	text.setColor(sf::Color::Black);

	description.setFont(font);
	description.setCharacterSize(25);
	description.setColor(sf::Color::White);

	focus = false;
}
KeyField::KeyField(std::shared_ptr<sf::RenderWindow> window, sf::Keyboard::Key key)
	: KeyField(window)
{
	this->key = key;

	sf::Event event;
	event.key.code = key;
	handleKeys(event);
}

void KeyField::setDescription(std::wstring str)
{
	description.setString(str);
	setTextPosition();
}

void KeyField::handleKeys(sf::Event & event)
{
	std::string ch = "?!";
	switch (event.key.code)
	{
	case sf::Keyboard::A:
		ch = "A";
		break;
	case sf::Keyboard::B:
		ch = "B";
		break;
	case sf::Keyboard::C:
		ch = "C";
		break;
	case sf::Keyboard::D:
		ch = 'D';
		break;
	case sf::Keyboard::E:
		ch = 'E';
		break;
	case sf::Keyboard::F:
		ch = 'F';
		break;
	case sf::Keyboard::G:
		ch = 'G';
		break;
	case sf::Keyboard::H:
		ch = 'H';
		break;
	case sf::Keyboard::I:
		ch = 'I';
		break;
	case sf::Keyboard::J:
		ch = 'J';
		break;
	case sf::Keyboard::K:
		ch = 'K';
		break;
	case sf::Keyboard::L:
		ch = 'L';
		break;
	case sf::Keyboard::M:
		ch = 'M';
		break;
	case sf::Keyboard::N:
		ch = 'N';
		break;
	case sf::Keyboard::O:
		ch = 'O';
		break;
	case sf::Keyboard::P:
		ch = 'P';
		break;
	case sf::Keyboard::Q:
		ch = 'Q';
		break;
	case sf::Keyboard::R:
		ch = 'R';
		break;
	case sf::Keyboard::S:
		ch = 'S';
		break;
	case sf::Keyboard::T:
		ch = 'T';
		break;
	case sf::Keyboard::U:
		ch = 'U';
		break;
	case sf::Keyboard::V:
		ch = 'V';
		break;
	case sf::Keyboard::W:
		ch = 'W';
		break;
	case sf::Keyboard::X:
		ch = 'X';
		break;
	case sf::Keyboard::Y:
		ch = 'Y';
		break;
	case sf::Keyboard::Z:
		ch = 'Z';
		break;
	case sf::Keyboard::Num0:
		ch = "0";
		break;
	case sf::Keyboard::Numpad0:
		ch = "Num 0";
		break;
	case sf::Keyboard::Num1:
		ch = "1";
		break;
	case sf::Keyboard::Numpad1:
		ch = "Num 1";
		break;
	case sf::Keyboard::Num2:
		ch = "2";
		break;
	case sf::Keyboard::Numpad2:
		ch = "Num 2";
		break;
	case sf::Keyboard::Num3:
		ch = "3";
		break;
	case sf::Keyboard::Numpad3:
		ch = "Num 3";
		break;
	case sf::Keyboard::Num4:
		ch = "4";
		break;
	case sf::Keyboard::Numpad4:
		ch = "Num 4";
		break;
	case sf::Keyboard::Num5:
		ch = "5";
		break;
	case sf::Keyboard::Numpad5:
		ch = "Num 5";
		break;
	case sf::Keyboard::Num6:
		ch = "6";
		break;
	case sf::Keyboard::Numpad6:
		ch = "Num 6";
		break;
	case sf::Keyboard::Num7:
		ch = "7";
		break;
	case sf::Keyboard::Numpad7:
		ch = "Num 7";
		break;
	case sf::Keyboard::Num8:
		ch = "8";
		break;
	case sf::Keyboard::Numpad8:
		ch = "Num 8";
		break;
	case sf::Keyboard::Num9:
		ch = "9";
		break;
	case sf::Keyboard::Numpad9:
		ch = "Num 9";
		break;
	case sf::Keyboard::Space:
		ch = "Space";
		break;
	case sf::Keyboard::BackSpace:
		ch = "Backspace";
		break;
	case sf::Keyboard::Left:
		ch = "Left";
		break;
	case sf::Keyboard::Right:
		ch = "Right";
		break;
	case sf::Keyboard::Up:
		ch = "Up";
		break;
	case sf::Keyboard::Down:
		ch = "Down";
		break;
	case sf::Keyboard::LShift:
		ch = "LShift";
		break;
	case sf::Keyboard::RShift:
		ch = "RShift";
		break;
	case sf::Keyboard::LAlt:
		ch = "LAlt";
		break;
	case sf::Keyboard::RAlt:
		ch = "RAlt";
		break;
	case sf::Keyboard::LControl:
		ch = "LCtr";
		break;
	case sf::Keyboard::RControl:
		ch = "RCtr";
		break;
	case sf::Keyboard::Tab:
		ch = "Tab";
		break;
	case sf::Keyboard::F1:
		ch = "F1";
		break;
	case sf::Keyboard::F2:
		ch = "F2";
		break;
	case sf::Keyboard::F3:
		ch = "F3";
		break;
	case sf::Keyboard::F4:
		ch = "F4";
		break;
	case sf::Keyboard::F5:
		ch = "F5";
		break;
	case sf::Keyboard::F6:
		ch = "F6";
		break;
	case sf::Keyboard::F7:
		ch = "F7";
		break;
	case sf::Keyboard::F8:
		ch = "F8";
		break;
	case sf::Keyboard::F9:
		ch = "F9";
		break;
	case sf::Keyboard::F10:
		ch = "F10";
		break;
	case sf::Keyboard::F11:
		ch = "F11";
		break;
	case sf::Keyboard::F12:
		ch = "F12";
		break;
	}

	key = event.key.code;
	text.setString(ch);
}

void KeyField::setTextPosition()
{
	sf::FloatRect text_dim = text.getLocalBounds();
	sf::FloatRect desc_dim = description.getLocalBounds();
	sf::FloatRect rect_dim = rectangle.getLocalBounds();
	sf::Vector2f rect_position = rectangle.getPosition();
	sf::Vector2f text_position;
	sf::Vector2f desc_position;
	text_position.x = (int)(rect_position.x + (rect_dim.width - text_dim.width) / 2.0f);
	text_position.y = (int)(rect_position.y + (rect_dim.height - text_dim.height) / 2.0f - 9.0f);
	desc_position.y = (int)(rect_position.y + (rect_dim.height - desc_dim.height) / 2.0f - 9.0f);
	desc_position.x = (int) (rect_position.x - desc_dim.width - 7.0f);
	text.setPosition(text_position);
	description.setPosition(desc_position);
}


void KeyField::handleEvents(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i coor(sf::Mouse::getPosition(*window));
		sf::Vector2f dim(rectangle.getSize());
		sf::Vector2f rec_coor(rectangle.getPosition());

		if (coor.x >= rec_coor.x && coor.x <= rec_coor.x + dim.x
			&& coor.y >= rec_coor.y && coor.y <= rec_coor.y + dim.y)
		{
			text.setString("");
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
		setTextPosition();
		focus = false;
		rectangle.setOutlineColor(sf::Color::Black);
	}
}

void KeyField::update(float deltaSeconds)
{

}

void KeyField::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(rectangle);
	window->draw(text);
	window->draw(description);
}

void KeyField::setDimensions(float width, float height)
{
	rectangle.setSize(sf::Vector2f(width, height));
}

void KeyField::setCoordinates(float x, float y)
{
	rectangle.setPosition(sf::Vector2f(x, y));
	text.setPosition(sf::Vector2f(x, y));
}