#include <iostream>
#include <cctype>

#include <SFML/Window.hpp>

#include "TextField.h"
#include "Control.h"


namespace
{
	const char* FONT_FILE = "font.ttf";
	const char NOT_ALLOWED_CHAR = '#';
	const float SECONDS_TO_CHANGE_CURSOR_VISIBILITY = 0.4f;
	const size_t TEXT_SIZE = 25;
	const sf::Color TEXT_COLOR(sf::Color::Black);
	const sf::Color FILL_COLOR(sf::Color::White);
	const sf::Vector2f TEXT_POSITION_OFFSET(3.0f, 3.0f);
	const float OUTLINE_THICKNESS = 2.0f;
	const sf::Color OUTLINE_COLOR(sf::Color::Black);
	const sf::Color OUTLINE_COLOR_FOCUSED(sf::Color::Yellow);
	const sf::Vector2f CURSOR_SIZE(2.0f, 28.0f);
	const sf::Vector2f CURSOR_POSITION_OFFSET(2.0f, 3.0f);
}

TextField::TextField(std::shared_ptr <sf::RenderWindow> window)
	: Control(window)
{
	initText();
	initRectangle();
	focus = false;
	initCursor();
}

void TextField::initText()
{
	if (!font.loadFromFile(FONT_FILE))
	{
		std::cout << "Cannot load font from file.\n";
	}

	text.setFont(font);
	text.setString("");
	text.setCharacterSize(TEXT_SIZE);
	text.setColor(TEXT_COLOR);
}

void TextField::initRectangle()
{
	rectangle.setFillColor(FILL_COLOR);
	rectangle.setOutlineThickness(OUTLINE_THICKNESS);
	rectangle.setOutlineColor(OUTLINE_COLOR);
}

void TextField::initCursor()
{
	cursor.setSize(CURSOR_SIZE);
	cursor.setFillColor(TEXT_COLOR);
}

void TextField::handleEvents(sf::Event & event)
{
	if (isMouseButtonReleased(event))
	{
		if (isMouseInside())
		{
			handleSetFocus();
		}
		else
		{
			handleUnsetFocus();
		}
	}
	else if (isFocusedAndKeyPressed(event))
	{
		handleKeys(event);
		refreshRenderedText();
	}
}

bool TextField::isMouseButtonReleased(sf::Event& event) const
{
	return (event.type == sf::Event::MouseButtonReleased);
}

bool TextField::isMouseInside() const
{
	sf::Vector2i coor(sf::Mouse::getPosition(*window));
	sf::Vector2f dim(rectangle.getSize());
	sf::Vector2f rec_coor(rectangle.getPosition());

	return (coor.x >= rec_coor.x && coor.x <= rec_coor.x + dim.x
		&& coor.y >= rec_coor.y && coor.y <= rec_coor.y + dim.y);
}

void TextField::handleSetFocus()
{
	focus = true;
	visible_cursor = true;
	seconds_to_change_cursor_visibility = SECONDS_TO_CHANGE_CURSOR_VISIBILITY;
	rectangle.setOutlineColor(OUTLINE_COLOR_FOCUSED);
}

void TextField::handleUnsetFocus()
{
	focus = false;
	rectangle.setOutlineColor(OUTLINE_COLOR);
}

bool TextField::isFocusedAndKeyPressed(sf::Event& event) const
{
	return (focus && event.type == sf::Event::KeyPressed);
}

void TextField::refreshRenderedText()
{
	printed_text = real_text;
	text.setString(printed_text);
	sf::FloatRect rect = text.getLocalBounds();
	sf::Vector2f position = text.getPosition() + CURSOR_POSITION_OFFSET;
	position.x += rect.width;
	cursor.setPosition(position);

	sf::Vector2f size = rectangle.getSize();

	while (rect.width > size.x)
	{
		float difference = rect.width - size.x;
		std::cout << "Too wide: " << difference << "\n";

		printed_text = printed_text.substring(1);
		text.setString(printed_text);
		rect = text.getLocalBounds();
		size = rectangle.getSize();

		position = text.getPosition() + CURSOR_POSITION_OFFSET;
		position.x += rect.width;
		cursor.setPosition(position);
	}
}

void TextField::handleKeys(sf::Event& event)
{
	char ch = getCharFromEventOrHandleBackspace(event);
	appendCharToRealTextIfAllowedChar(ch);
}

char TextField::getCharFromEventOrHandleBackspace(sf::Event& event)
{
	char ch = NOT_ALLOWED_CHAR;
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
	case sf::Keyboard::Dash:
		ch = '-';
		break;
	case sf::Keyboard::Period:
		ch = '.';
		break;
	case sf::Keyboard::BackSpace:
		handleBackspace();
		break;
	}

	return ch;
}

void TextField::handleBackspace()
{
	sf::String str = real_text.toAnsiString();
	str = str.substring(0, str.getSize() - 1);
	real_text = str;
}

void TextField::appendCharToRealTextIfAllowedChar(char ch)
{
	if (isAllowedChar(ch))
	{
		if (isToupper(ch))
		{
			ch = toupper(ch);
		}
		appendCharToRealText(ch);
	}
}

bool TextField::isAllowedChar(char ch) const
{
	return ch != NOT_ALLOWED_CHAR;
}

bool TextField::isToupper(char ch) const
{
	return isShiftPressed() && isalpha(ch);
}

bool TextField::isShiftPressed() const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::RShift));
}

void TextField::appendCharToRealText(char ch)
{
	std::cout << ch << std::endl;
	sf::String str = real_text.toAnsiString();
	str += ch;
	real_text = str;
}

void TextField::update(float delta_seconds)
{
	seconds_to_change_cursor_visibility -= delta_seconds;

	if (seconds_to_change_cursor_visibility <= 0.0f)
	{
		seconds_to_change_cursor_visibility += SECONDS_TO_CHANGE_CURSOR_VISIBILITY;
		visible_cursor = !visible_cursor;
	}
}

void TextField::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(rectangle);
	window->draw(text);
	if (focus && visible_cursor)
	{
		window->draw(cursor);
	}
}

void TextField::setDimensions(float width, float height)
{
	rectangle.setSize(sf::Vector2f(width, height));
}

void TextField::setPosition(sf::Vector2f position)
{
	rectangle.setPosition(position);
	text.setPosition(position + TEXT_POSITION_OFFSET);
	cursor.setPosition(position + TEXT_POSITION_OFFSET + CURSOR_POSITION_OFFSET);
}