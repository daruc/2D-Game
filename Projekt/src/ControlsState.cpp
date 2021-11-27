#include <iostream>
#include <fstream>
#include <thread>

#include "GUI/KeyField.h"
#include "GUI/Button.h"

#include "ControlsState.h"
#include "MainManuState.h"
#include "Strings.h"
#include "FontSingleton.h"
#include "GUI/GUIConstants.h"


namespace
{
	const sf::Vector2f KEY_FIELD_DIMENSIONS(120.0f, 40.0f);
}


ControlsState::ControlsState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	float center = window->getSize().x / 2;
	Strings* strings = Strings::Instance();
	initBack(window, strings);

	controls_manager.load();

	initLeftField(window, controls_manager, center, strings);
	initRightField(window, controls_manager, center, strings);
	initCrouchField(window, controls_manager, center, strings);
	initJumpField(window, controls_manager, center, strings);
	initSaveButton(window, center, strings);
	initTitle(strings);
	initBackground(window);
}

void ControlsState::initBack(std::shared_ptr<sf::RenderWindow>& window, Strings* strings)
{
	std::shared_ptr<Button> back = std::make_shared<Button>(window, strings->get("main_menu"));
	back->setPosition(sf::Vector2f(20.0f, 20.0f));
	back->setDimensions(sf::Vector2f(200.0f, 40.0f));
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(back);
}

void ControlsState::initRightField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center, Strings* strings)
{
	right_field = std::make_shared<KeyField>(window, controls_manager.getRight());
	right_field->setDimensions(KEY_FIELD_DIMENSIONS);
	right_field->setPosition(sf::Vector2f(center - 60.0f, 150.0f));
	right_field->setDescription(strings->get("turn_right"));
	controls.push_back(right_field);
}

void ControlsState::initLeftField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center,
	Strings* strings)
{
	left_field = std::make_shared<KeyField>(window, controls_manager.getLeft());
	left_field->setDimensions(KEY_FIELD_DIMENSIONS);
	left_field->setPosition(sf::Vector2f(center - 60.0f, 100.0f));
	left_field->setDescription(strings->get("turn_left"));
	controls.push_back(left_field);
}

void ControlsState::initCrouchField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center, Strings* strings)
{
	crouch_field = std::make_shared<KeyField>(window, controls_manager.getCrouch());
	crouch_field->setDimensions(KEY_FIELD_DIMENSIONS);
	crouch_field->setPosition(sf::Vector2f(center - 60.0f, 200.0f));
	crouch_field->setDescription(strings->get("crouch"));
	controls.push_back(crouch_field);
}

void ControlsState::initJumpField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center, Strings* strings)
{
	jump_field = std::make_shared<KeyField>(window, controls_manager.getJump());
	jump_field->setDimensions(KEY_FIELD_DIMENSIONS);
	jump_field->setPosition(sf::Vector2f(center - 60.0f, 250.0f));
	jump_field->setDescription(strings->get("jump"));
	controls.push_back(jump_field);
}

void ControlsState::initSaveButton(std::shared_ptr<sf::RenderWindow>& window, float center, Strings* strings)
{
	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, strings->get("save"));
	save_button->setDimensions(sf::Vector2f(100.0f, 40.0f));
	save_button->setPosition(sf::Vector2f(center - 50.0f, 400.0f));
	save_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		controls_manager.setLeft(left_field->getKey());
		controls_manager.setRight(right_field->getKey());
		controls_manager.setJump(jump_field->getKey());
		controls_manager.setCrouch(crouch_field->getKey());
		controls_manager.save();
	});
	controls.push_back(save_button);
}

void ControlsState::initTitle(Strings* strings)
{
	title.setString(strings->get("controls_title"));
	title.setPosition(250.0f, 20.0f);
	title.setFont(FontSingleton::getInstance()->getFont());
}

void ControlsState::initBackground(std::shared_ptr<sf::RenderWindow>& window)
{
	background.setFillColor(GUIConstants::HEADER_COLOR);
	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
}

ControlsState::~ControlsState()
{

}

void ControlsState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleExitEvent(event);
		handleControlsEvent(event);
	}
}

void ControlsState::handleExitEvent(sf::Event & event)
{
	if (event.type == sf::Event::Closed)
	{
		window->close();
	}
}

void ControlsState::handleControlsEvent(sf::Event event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void ControlsState::update(float delta_seconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(delta_seconds);
	}
}

void ControlsState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(GUIConstants::BACKGROUND_COLOR);
	window->draw(background);
	drawControls(window);
	window->draw(title);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void ControlsState::drawControls(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}