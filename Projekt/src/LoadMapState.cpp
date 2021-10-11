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
	float center_x = window->getSize().x / 2;
	float center_y = window->getSize().y / 2;
	Strings* strings = Strings::Instance();
	prev_map = map;
	std::shared_ptr<TextField> text_field = std::make_shared<TextField>(window);
	text_field->setCoordinates(center_x - 180.0f, center_y - 20.0f);
	text_field->setDimensions(300.0f, 40.0f);
	controls.push_back(text_field);

	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->get("load"));
	load_button->setCoordinates(center_x + 130.0f, center_y - 20.0f);
	load_button->setDimensions(100.0f, 40.0f);
	load_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;

		MapBuilder map_builder(window);
		map_builder.loadFromFile(text_field->getString().toWideString());
		std::shared_ptr<Map> map = map_builder.get();
		this->State::nextState = std::make_shared<EditorState>(window, map);
	});
	controls.push_back(load_button);

	std::shared_ptr<Button> editor_button = std::make_shared<Button>(window, strings->get("editor"));
	editor_button->setCoordinates(20.0f, 20.0f);
	editor_button->setDimensions(130.0f, 40.0f);
	editor_button->addListener([this](std::string str)->void {
		State::nextState = std::make_shared<EditorState>(State::window, prev_map);
	});
	controls.push_back(editor_button);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->get("load_map_title"));
	title.setPosition(180.0f, 20.0f);
	title.setFont(font);

	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
	background.setFillColor(sf::Color(0, 0, 80, 255));
}
LoadMapState::~LoadMapState()
{

}

void LoadMapState::handleEvents()
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
void LoadMapState::update(float deltaSeconds)
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update(deltaSeconds);
	}
}

void LoadMapState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw(window);
	}
	window->draw(title);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}