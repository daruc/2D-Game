#include <iostream>
#include <fstream>
#include <thread>

#include "LoadMapState.h"
#include "GUI/TextField.h"
#include "GUI/Button.h"
#include "Map.h"
#include "Editor/EditorState.h"
#include "Strings.h"
#include "MapBuilder.h"


LoadMapState::LoadMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window)
{
	Strings* strings = Strings::Instance();
	prev_map = map;

	createTextField(window);
	createLoadButton(window, strings);
	createEditorButton(window, strings);
	initTitle(strings);
	initBackground();
}

void LoadMapState::createTextField(std::shared_ptr<sf::RenderWindow> window)
{
	sf::Vector2f centerOffset(-180.0f, -20.0f);

	text_field = std::make_shared<TextField>(window);
	text_field->setPosition(getScreenCenter(window) + centerOffset);
	text_field->setDimensions(300.0f, 40.0f);
	controls.push_back(text_field);
}

void LoadMapState::createLoadButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	sf::Vector2f centerOffset(130.0f, -20.0f);
	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->get("load"));
	load_button->setPosition(getScreenCenter(window) + centerOffset);
	load_button->setDimensions(sf::Vector2f(100.0f, 40.0f));
	load_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;

		MapBuilder map_builder(window);
		map_builder.loadFromFile(text_field->getString());
		std::shared_ptr<Map> map = map_builder.get();
		this->State::nextState = std::make_shared<EditorState>(window, map);
	});
	controls.push_back(load_button);
}

void LoadMapState::createEditorButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	std::shared_ptr<Button> editor_button = std::make_shared<Button>(window, strings->get("editor"));
	editor_button->setPosition(sf::Vector2f(20.0f, 20.0f));
	editor_button->setDimensions(sf::Vector2f(130.0f, 40.0f));
	editor_button->addListener([this](std::string str)->void {
		State::nextState = std::make_shared<EditorState>(State::window, prev_map);
	});
	controls.push_back(editor_button);
}

void LoadMapState::initTitle(Strings* strings)
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->get("load_map_title"));
	title.setPosition(180.0f, 20.0f);
	title.setFont(font);
}

void LoadMapState::initBackground()
{
	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
	background.setFillColor(sf::Color(0, 0, 80, 255));
}

sf::Vector2f LoadMapState::getScreenCenter(std::shared_ptr<sf::RenderWindow> window) const
{
	return sf::Vector2f(window->getSize()) / 2.0f;
}

LoadMapState::~LoadMapState()
{

}

void LoadMapState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleExitEvent(event);
		handleControlsEvents(event);
	}
}

void LoadMapState::handleExitEvent(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window->close();
	}
}

void LoadMapState::handleControlsEvents(sf::Event& event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void LoadMapState::update(float delta_seconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(delta_seconds);
	}
}

void LoadMapState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);
	drawControls(window);
	window->draw(title);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void LoadMapState::drawControls(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}