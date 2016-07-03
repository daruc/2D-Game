#include <iostream>
#include <memory>
#include "Button.h"
#include "MapMenuState.h"
#include "GameOverState.h"
#include "Strings.h"

GameOverState::GameOverState(std::shared_ptr<sf::RenderWindow> window, bool isWin)
	: State(window)
{
	Strings* strings = Strings::Instance();
	std::shared_ptr<Button> back = std::make_shared<Button>(window, strings->getNewGame());
	back->setCoordinates(20.0f, 20.0f);
	back->setDimensions(200.0f, 40.0f);
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MapMenuState>(State::window);
	});
	controls.push_back(back);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	if (isWin)
	{
		title.setString(strings->getWin());
	}
	else
	{
		title.setString(strings->getDefeat());
	}
	title.setPosition(250.0f, 20.0f);
	title.setFont(font);

	background.setSize(sf::Vector2f(800.0f, 80.0f));
	background.setFillColor(sf::Color(0, 0, 80, 255));
}

GameOverState::~GameOverState()
{

}
void GameOverState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else
		{
			auto begin = controls.begin();
			auto end = controls.end();
			for (auto it = begin; it != end; ++it)
			{
				(*it)->handleEvents(event);
			}
		}
	}
}
void GameOverState::update()
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update();
	}
}

void GameOverState::draw()
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);

	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw();
	}

	window->draw(title);
	window->display();
}