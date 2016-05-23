#include "MapMenuState.h"

MapMenuState::MapMenuState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
}

MapMenuState::~MapMenuState()
{

}

void MapMenuState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void MapMenuState::update()
{

}

void MapMenuState::draw()
{
	window->clear();
	window->display();
}