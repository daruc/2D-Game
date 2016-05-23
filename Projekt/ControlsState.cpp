#include "ControlsState.h"

ControlsState::ControlsState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{}

ControlsState::~ControlsState()
{

}

void ControlsState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void ControlsState::update()
{

}

void ControlsState::draw()
{
	window->clear();
	window->display();
}