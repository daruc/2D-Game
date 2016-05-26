#include "LoadMapState.h"

LoadMapState::LoadMapState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{

}
LoadMapState::~LoadMapState()
{

}

void LoadMapState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}
void LoadMapState::update()
{

}
void LoadMapState::draw()
{
	window->clear();
	window->display();
}