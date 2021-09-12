#include <string>
#include "App.h"
#include "MainManuState.h"


void App::init()
{
	int width = 800;
	int height = 600;
	std::string title("Gra");
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title,
		sf::Style::Close | sf::Style::Titlebar);
	currentState = std::make_shared<MainMenuState>(window);
	
}

void App::run()
{
	while (window->isOpen())
	{
		currentState->handleEvents();
		currentState->update();
		currentState->draw(window);

		if (currentState->getNextState() != nullptr)
		{
			currentState = currentState->getNextState();
		}
	}

}