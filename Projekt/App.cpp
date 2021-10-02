#include <string>
#include "App.h"
#include "MainManuState.h"


void App::init()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE,
		sf::Style::Close | sf::Style::Titlebar);
	currentState = std::make_shared<MainMenuState>(window);
}

void App::run()
{
	sf::Clock clock;

	while (window->isOpen())
	{
		currentState->handleEvents();
		float deltaSeconds = clock.getElapsedTime().asSeconds();
		clock.restart();
		currentState->update(deltaSeconds);
		currentState->draw(window);
		changeCurrentState();
	}
}

void App::changeCurrentState()
{
	if (currentState->getNextState() != nullptr)
	{
		currentState = currentState->getNextState();
	}
}