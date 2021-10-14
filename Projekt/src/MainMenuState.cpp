#include <iostream>
#include <memory>
#include <thread>
#include "MainManuState.h"
#include "MapMenuState.h"
#include "Editor/EditorState.h"
#include "ControlsState.h"
#include "Control.h"
#include "GUI/Button.h"
#include "Strings.h"


namespace
{
	const sf::Vector2f BUTTON_DIMENSIONS(200.0f, 50.0f);
}

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	Strings* strings = Strings::Instance();
	createNewGameButton(window, strings);
	createControlsButton(window, strings);
	createEditorButton(window, strings);
	createExitButton(window, strings);
}

sf::Vector2f MainMenuState::getScreenCenter(std::shared_ptr<sf::RenderWindow> window) const
{
	return sf::Vector2f(window->getSize()) / 2.0f;
}

void MainMenuState::createNewGameButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	sf::Vector2f centerOffset(-100.0f, -200.0f);
	std::shared_ptr<Button> new_game_button = std::make_shared<Button>(window, strings->get("new_game"));
	new_game_button->setPosition(getScreenCenter(window) + centerOffset);
	new_game_button->setDimensions(BUTTON_DIMENSIONS);
	new_game_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<MapMenuState>(State::window);
	});
	controls.push_back(new_game_button);
}

void MainMenuState::createControlsButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	sf::Vector2f centerOffset(-100.0f, -100.0f);
	std::shared_ptr<Button> controls_button = std::make_shared<Button>(window, strings->get("controls"));
	controls_button->setPosition(getScreenCenter(window) + centerOffset);
	controls_button->setDimensions(BUTTON_DIMENSIONS);
	controls_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<ControlsState>(State::window);
	});
	controls.push_back(controls_button);
}

void MainMenuState::createEditorButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	sf::Vector2f centerOffset(-100.0f, 0.0f);
	std::shared_ptr<Button> edit_button = std::make_shared<Button>(window, strings->get("editor"));
	edit_button->setPosition(getScreenCenter(window) + centerOffset);
	edit_button->setDimensions(BUTTON_DIMENSIONS);
	edit_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<EditorState>(State::window);
	});
	controls.push_back(edit_button);
}

void MainMenuState::createExitButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	sf::Vector2f centerOffset(-100.0f, 100.0f);
	std::shared_ptr<Button> exit_button = std::make_shared<Button>(window, strings->get("exit"));
	exit_button->setPosition(getScreenCenter(window) + centerOffset);
	exit_button->setDimensions(BUTTON_DIMENSIONS);
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
		handleExitEvent(event);
		handleControlsEvent(event);
	}
}

void MainMenuState::handleExitEvent(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window->close();
	}
}

void MainMenuState::handleControlsEvent(sf::Event& event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void MainMenuState::update(float deltaSeconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(deltaSeconds);
	}
}

void MainMenuState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	State::window->clear(sf::Color(0, 0, 100, 255));
	drawControls(window);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void MainMenuState::drawControls(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}