#include <string>
#include "App.h"
#include "MainManuState.h"


void App::init()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE,
		sf::Style::Close | sf::Style::Titlebar);
	current_state = std::make_shared<MainMenuState>(window);
}

void App::run()
{
	sf::Clock clock;

	while (window->isOpen())
	{
		current_state->handleEvents();
		float delta_seconds = clock.getElapsedTime().asSeconds();
		clock.restart();
		current_state->update(delta_seconds);
		current_state->draw(window);
		changeCurrentState();
	}
}

void App::changeCurrentState()
{
	if (current_state->getNextState() != nullptr)
	{
		current_state = current_state->getNextState();
	}
}