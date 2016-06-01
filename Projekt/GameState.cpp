#include <iostream>
#include "GameState.h"
#include "MapMenuState.h"
#include "Utils.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window), physics(window, map)
{
	this->map = map;
	textures.loadCursor();
	cursor.setTexture(*textures.getCursor(), true);
	cursor.setOrigin(16.0f, 16.0f);
	cursor.setPosition(.0f, 0.0f);

	window->setMouseCursorVisible(false);

	player.setPosition(map->getPlayerPosition());
	player.setFillColor(sf::Color::Green);
	float width = meters2pixels(1.0f);
	float height = meters2pixels(2.0f);
	player.setSize(sf::Vector2f(width, height));
	player.setOrigin(sf::Vector2f(width / 2, height / 2));
}

GameState::~GameState()
{

}

void GameState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->setMouseCursorVisible(true);
				State::nextState = std::make_shared<MapMenuState>(window);
			}
		}
	}
}
void GameState::update()
{
	//update Cursor position
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	cursor.setPosition(sf::Vector2f(mouse.x, mouse.y));

	//calculate physics
	physics.simulate();
	
	player.setPosition(map->getPlayerPosition());
	view = window->getDefaultView();
	
}
void GameState::draw()
{
	window->clear();
	map->draw(*window);
	window->draw(player);

	window->draw(cursor);
	window->display();
};