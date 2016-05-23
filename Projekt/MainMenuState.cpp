#include <iostream>
#include <memory>
#include "MainManuState.h"
#include "MapMenuState.h"
#include "ControlsState.h"
#include "Control.h"
#include "Button.h"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	std::shared_ptr<Button> new_game_button = std::make_shared<Button>(window, "Nowa gra");
	new_game_button->setCoordinates(300.0f, 100.0f);
	new_game_button->setDimensions(200.0f, 50.0f);
	new_game_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<MapMenuState>(State::window);
	});
	controls.push_back(new_game_button);

	std::shared_ptr<Button> controls_button = std::make_shared<Button>(window, "Sterowanie");
	controls_button->setCoordinates(300.0f, 200.0f);
	controls_button->setDimensions(200.0f, 50.0f);
	controls_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<ControlsState>(State::window);
	});
	controls.push_back(controls_button);

	std::shared_ptr<Button> exit_button = std::make_shared<Button>(window, "Wyjœcie");
	exit_button->setCoordinates(300.0f, 300.0f);
	exit_button->setDimensions(200.0f, 50.0f);
	exit_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		this->window->close();
	});
	controls.push_back(exit_button);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void MainMenuState::update()
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update();
	}
}

void MainMenuState::draw()
{
	State::window->clear();

	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw();
	}

	
	window->display();
}