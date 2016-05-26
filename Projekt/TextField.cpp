#include "TextField.h"
#include "Control.h"

TextField::TextField(std::shared_ptr <sf::RenderWindow> window)
	: Control(window)
{

}

void TextField::handleEvents(sf::Event & event)
{
	
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