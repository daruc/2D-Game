#include <iostream>
#include <sstream>
#include "GameState.h"
#include "MapMenuState.h"
#include "GameOverState.h"
#include "Utils.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window), physics(window, map)
{
	this->map = map;
	textures.loadCursor();
	textures.loadMapType(map->getType());
	map->setGroundTexture(textures.getGround());
	cursor.setTexture(*textures.getCursor(), true);
	cursor.setOrigin(16.0f, 16.0f);
	cursor.setPosition(.0f, 0.0f);

	font.loadFromFile("font.ttf");
	txtTime.setFont(font);
	txtTime.setString("0");
	sf::Vector2u resolution = State::window->getSize();
	txtTime.setCharacterSize(17.0f);
	txtTime.setPosition(resolution.x / 2, 0.0f);


	window->setMouseCursorVisible(false);

	player.setPosition(map->getPlayerPosition());
	player.setFillColor(sf::Color::Green);
	float width = meters2pixels(1.0f);
	float height = meters2pixels(2.0f);
	player.setSize(sf::Vector2f(width, height));
	player.setOrigin(sf::Vector2f(width / 2, height / 2));

	finish.setPosition(map->getFinishPosition());
	finish.setFillColor(sf::Color::Red);
	width = meters2pixels(1.0f);
	height = meters2pixels(1.0f);
	finish.setSize(sf::Vector2f(width, height));
	finish.setOrigin(sf::Vector2f(width / 2, height / 2));

	view.setSize(800.0f, 600.0f);

	view.move(player.getPosition() - view.getCenter());

	clock.restart();
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
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				std::cout << "click fire\n";
				sf::Vector2f mouse = cursor.getPosition();
				sf::Vector2f playerPosition = player.getPosition();
				sf::Vector2u resolution = window->getSize();

				physics.throwBullet(playerPosition.x, playerPosition.y,
					mouse.x - resolution.x / 2, mouse.y - resolution.y / 2);
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

	//set camera
	view.setCenter(player.getPosition());

	//check if the game is over
	if (physics.isWin())
	{
		window->setMouseCursorVisible(true);
		State::nextState = std::make_shared<GameOverState>(window, true);

		std::cout << "win, time = " << clock.getElapsedTime().asSeconds() << std::endl;
	}
	if (physics.isDead())
	{
		window->setMouseCursorVisible(true);
		State::nextState = std::make_shared<GameOverState>(window, false);

		std::cout << "defeated, time = " << clock.getElapsedTime().asSeconds() << std::endl;
	}


	//new thread
	float seconds = clock.getElapsedTime().asMilliseconds() / 1000.0;
	std::stringstream stream;
	stream.precision(1);
	stream << std::fixed << seconds;
	txtTime.setString(stream.str());
}
void GameState::draw()
{
	window->clear();

	window->setView(view);
	map->draw(*window);
	window->draw(player);
	window->draw(finish);
	
	window->setView(window->getDefaultView());
	
	window->draw(cursor);
	window->draw(txtTime);
	window->display();
};