#include "Control.h"

Control::Control(std::shared_ptr <sf::RenderWindow> window)
{
	this->window = window;
}

void Control::addListener(std::function<void(std::string)> listener)
{
	this->listener = listener;
}