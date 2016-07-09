#include <string>
#include "App.h"
#include "MainManuState.h"

App::App()
{

}

App::~App()
{

}

void App::init()
{
	int width = sf::VideoMode::getDesktopMode().width;
	int height = sf::VideoMode::getDesktopMode().height;
	std::string title("Gra");
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title,
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
	currentState = std::make_shared<MainMenuState>(window);
	
}

void App::run()
{
	while (window->isOpen())
	{
		currentState->handleEvents();
		currentState->update();
		currentState->draw();

		if (currentState->getNextState() != nullptr)
		{
			currentState = currentState->getNextState();
		}
	}

}