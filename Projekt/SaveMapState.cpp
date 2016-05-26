#include "Map.h"
#include "SaveMapState.h"

SaveMapState::SaveMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window)
{
	this->map = map;
}

SaveMapState::~SaveMapState()
{

}

void SaveMapState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void SaveMapState::update()
{

}

void SaveMapState::draw()
{
	window->clear();
	window->display();
}