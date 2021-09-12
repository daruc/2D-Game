#include <iostream>
#include <memory>
#include <thread>
#include "MainManuState.h"
#include "MapMenuState.h"
#include "EditorState.h"
#include "ControlsState.h"
#include "Control.h"
#include "Button.h"
#include "Strings.h"


MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	float center = window->getSize().x / 2;
	Strings* strings = Strings::Instance();
	std::shared_ptr<Button> new_game_button = std::make_shared<Button>(window, strings->get("new_game"));
	new_game_button->setCoordinates(center - 100.0f, 100.0f);
	new_game_button->setDimensions(200.0f, 50.0f);
	new_game_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<MapMenuState>(State::window);
	});
	controls.push_back(new_game_button);

	std::shared_ptr<Button> controls_button = std::make_shared<Button>(window, strings->get("controls"));
	controls_button->setCoordinates(center - 100.0f, 200.0f);
	controls_button->setDimensions(200.0f, 50.0f);
	controls_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<ControlsState>(State::window);
	});
	controls.push_back(controls_button);

	std::shared_ptr<Button> edit_button = std::make_shared<Button>(window, strings->get("editor"));
	edit_button->setCoordinates(center - 100.0f, 300.0f);
	edit_button->setDimensions(200.0f, 50.0f);
	edit_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<EditorState>(State::window);
	});
	controls.push_back(edit_button);

	std::shared_ptr<Button> exit_button = std::make_shared<Button>(window, strings->get("exit"));
	exit_button->setCoordinates(center - 100.0f, 400.0f);
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
		else {
			auto begin = controls.begin();
			auto end = controls.end();
			for (auto it = begin; it != end; ++it)
			{
				(*it)->handleEvents(event);
			}
		}
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

void MainMenuState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	State::window->clear(sf::Color(0, 0, 100, 255));

	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw(window);
	}

	
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}