#include <iostream>
#include "KeyField.h"
#include "../Utils/Utils.h"
#include "../FontSingleton.h"
#include "GUIConstants.h"


namespace
{
	const float OUTLINE_THICKNESS = 3.0f;
	const sf::Color FILL_COLOR(sf::Color::White);
	const sf::Color OUTLINE_COLOR(sf::Color::Black);
	const sf::Vector2f TEXT_POSITION_OFFSET(0.0f, -9.0f);
	const sf::Vector2f DESCRIPTION_POSITION_OFFSET(-7.0f, -9.0f);
}

KeyField::KeyField(std::shared_ptr<sf::RenderWindow> window)
	: Control(window)
{
	initRectangle();
	initKeyText();
	initDescription();

	focus = false;
}

void KeyField::initRectangle()
{
	rectangle.setFillColor(FILL_COLOR);
	rectangle.setOutlineThickness(OUTLINE_THICKNESS);
	rectangle.setOutlineColor(OUTLINE_COLOR);
}

void KeyField::initKeyText()
{
	text.setFont(FontSingleton::getInstance()->getFont());
	text.setCharacterSize(GUIConstants::BUTTON_TEXT_SIZE);
	text.setColor(GUIConstants::BUTTON_TEXT_COLOR);
}

void KeyField::initDescription()
{
	description.setFont(FontSingleton::getInstance()->getFont());
	description.setCharacterSize(GUIConstants::BUTTON_TEXT_SIZE);
	description.setColor(GUIConstants::LABEL_TEXT_COLOR);
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
	case sf::Keyboard::Enter:
		ch = "Enter";
		break;
	case sf::Keyboard::Equal:
		ch = "=";
		break;
	case sf::Keyboard::SemiColon:
		ch = ";";
		break;
	case sf::Keyboard::Hyphen:
		ch = "-";
		break;
	case sf::Keyboard::LBracket:
		ch = "[";
		break;
	case sf::Keyboard::RBracket:
		ch = "]";
		break;
	case sf::Keyboard::Period:
		ch = ".";
		break;
	case sf::Keyboard::LSystem:
		ch = "LWindow";
		break;
	case sf::Keyboard::RSystem:
		ch = "RWindow";
		break;
	case sf::Keyboard::Insert:
		ch = "Insert";
		break;
	case sf::Keyboard::Delete:
		ch = "Delete";
		break;
	case sf::Keyboard::Add:
		ch = "+";
		break;
	case sf::Keyboard::Subtract:
		ch = "Num -";
		break;
	case sf::Keyboard::Multiply:
		ch = "*";
		break;
	case sf::Keyboard::Divide:
		ch = "/";
		break;
	case sf::Keyboard::Pause:
		ch = "Pause";
		break;
	case sf::Keyboard::Quote:
		ch = "'";
		break;
	case sf::Keyboard::Tilde:
		ch = "~";
		break;
	case sf::Keyboard::Home:
		ch = "Home";
		break;
	case sf::Keyboard::End:
		ch = "End";
		break;
	case sf::Keyboard::Slash:
		ch = "/";
		break;
	case sf::Keyboard::BackSlash:
		ch = "\\";
		break;
	case sf::Keyboard::Menu:
		ch = "Menu";
		break;
	case sf::Keyboard::Escape:
		ch = "Escape";
		break;
	case sf::Keyboard::Comma:
		ch = ",";
		break;
	}

	key = event.key.code;
	text.setString(ch);
}

void KeyField::setTextPosition()
{
	sf::Vector2f text_dim = rectDimensions(text.getLocalBounds());
	sf::Vector2f desc_dim = rectDimensions(description.getLocalBounds());
	sf::Vector2f rect_dim = rectDimensions(rectangle.getLocalBounds());
	sf::Vector2f rect_position = rectangle.getPosition();

	sf::Vector2f text_center_in_rect = (rect_dim - text_dim) / 2.0f;
	sf::Vector2f text_position = rect_position + text_center_in_rect + TEXT_POSITION_OFFSET;

	float desc_y_center = (rect_dim.y - desc_dim.y) / 2.0f;
	sf::Vector2f desc_position = rect_position + DESCRIPTION_POSITION_OFFSET;
	desc_position.x -= desc_dim.x;
	desc_position.y += desc_y_center;

	text.setPosition(text_position);
	description.setPosition(desc_position);
}

void KeyField::handleEvents(sf::Event & event)
{
	if (isMouseButtonReleased(event))
	{
		if (isMouseInsideRectangle())
		{
			setFocus();
		}
		else
		{
			unsetFocus();
		}
	}
	else if (isFocusedKeyPressed(event))
	{
		assignKey(event);
	}
}

bool KeyField::isMouseButtonReleased(sf::Event& event) const
{
	return (event.type == sf::Event::MouseButtonReleased);
}

bool KeyField::isMouseInsideRectangle() const
{
	sf::Vector2i coor(sf::Mouse::getPosition(*window));
	sf::Vector2f dim(rectangle.getSize());
	sf::Vector2f rec_coor(rectangle.getPosition());

	return (coor.x >= rec_coor.x && coor.x <= rec_coor.x + dim.x
		&& coor.y >= rec_coor.y && coor.y <= rec_coor.y + dim.y);
}

void KeyField::setFocus()
{
	text.setString("");
	focus = true;
	rectangle.setOutlineColor(sf::Color::Yellow);
}

void KeyField::unsetFocus()
{
	focus = false;
	rectangle.setOutlineColor(sf::Color::Black);
}

bool KeyField::isFocusedKeyPressed(sf::Event& event) const
{
	return (focus && event.type == sf::Event::KeyPressed);
}

void KeyField::assignKey(sf::Event& event)
{
	handleKeys(event);
	setTextPosition();
	focus = false;
	rectangle.setOutlineColor(sf::Color::Black);
}

void KeyField::update(float delta_seconds)
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

void KeyField::setPosition(sf::Vector2f position)
{
	rectangle.setPosition(position);
	text.setPosition(position);
}