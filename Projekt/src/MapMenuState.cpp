#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

#include "MapMenuState.h"
#include "MainManuState.h"
#include "GameState/GameState.h"
#include "GUI/TextField.h"
#include "GUI/Button.h"
#include "Map.h"
#include "Strings.h"
#include "MapBuilder.h"
#include "GUI/MapButton.h"
#include "GUI/TextField.h"


namespace
{
	const sf::Vector2f MAP_BUTTON_DIMENSIONS(100.0f, 100.0f);
	const float MAP_BUTTON_SPACE = 20.0f;
	const size_t MAPS_COUNT = 18;
	const size_t GRID_LAYOUT_COLUMNS = 6;
	const char* COMPLETED_MAPS_FILE = "maps.bin";
}

MapMenuState::MapMenuState(std::shared_ptr<sf::RenderWindow> window)
	: State(window), grid_layout(GRID_LAYOUT_COLUMNS)
{
	Strings* strings = Strings::Instance();
	grid_layout.setPosition(calculateMapGridPosition());
	sf::Vector2f screen_center = calculateScreenCenter();
	sf::Vector2f resolution(window->getSize());

	createMapButtons(strings);
	createBackButton(strings);
	createMapTextField();
	createLoadMapButton(strings);
	initTitle(strings);
	initBackground();
}

void MapMenuState::createMapButtons(Strings* strings)
{
	std::ifstream fin;
	fin.open(COMPLETED_MAPS_FILE, std::ios::binary);

	for (size_t map_index = 0; map_index < MAPS_COUNT; ++map_index)
	{
		char completed_as_char;
		fin >> completed_as_char;
		bool completed = static_cast<bool>(completed_as_char);

		createMapButton(strings, map_index, completed);
	}

	fin.close();
}

void MapMenuState::createMapButton(Strings* strings, size_t map_index, bool completed)
{
	std::string map_name = buildMapNameForIndex(map_index);

	auto map_button = std::make_shared<MapButton>(window, strings->get(map_name.c_str()));
	map_button->setDimensions(MAP_BUTTON_DIMENSIONS);
	map_button->addListener([=](std::string str)->void {
		std::cout << map_name << std::endl;
		MapBuilder mapBuilder(window);
		std::string map_file_path = buildMapFilePathForIndex(map_index);
		mapBuilder.loadFromFile(map_file_path);
		std::shared_ptr<Map> map = mapBuilder.get();
		State::nextState = std::make_shared<GameState>(State::window, map, map_index);
	});

	map_button->setCompleted(completed);
	grid_layout.addControl(map_button);
}

std::string MapMenuState::buildMapNameForIndex(size_t map_index)
{
	std::stringstream map_name_stream;
	map_name_stream << "map_" << (map_index + 1);
	return map_name_stream.str();
}

std::string MapMenuState::buildMapFilePathForIndex(size_t map_index)
{
	std::string map_file_path("maps\\");
	map_file_path += buildMapNameForIndex(map_index);
	return map_file_path;
}

void MapMenuState::createBackButton(Strings* strings)
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

void MapMenuState::createMapTextField()
{
	sf::Vector2f screen_center = calculateScreenCenter();
	sf::Vector2f resolution(window->getSize());

	sf::Vector2f position(screen_center.x - 200.0f, resolution.y - 60.0f);

	text_field = std::make_shared<TextField>(window);
	text_field->setPosition(position);
	text_field->setDimensions(250.0f, 40.0f);
	controls.push_back(text_field);
}

void MapMenuState::createLoadMapButton(Strings* strings)
{
	sf::Vector2f screen_center = calculateScreenCenter();
	sf::Vector2f resolution(window->getSize());

	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->get("load"));
	load_button->setPosition(sf::Vector2f(screen_center.x - 200.0f + 270.0f, resolution.y - 60.0f));
	load_button->setDimensions(sf::Vector2f(130.0f, 40.0f));
	load_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;

		std::stringstream sstream;
		sstream << "user_maps\\" << text_field->getString().toAnsiString();

		MapBuilder mapBuilder(window);
		bool exist = mapBuilder.loadFromFile(sstream.str());
		if (exist)
		{
			std::shared_ptr<Map> map = mapBuilder.get();
			State::nextState = std::make_shared<GameState>(State::window, map);
		}
	});
	controls.push_back(load_button);
}

void MapMenuState::initTitle(Strings* strings)
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->get("map_menu_title"));
	title.setPosition(250.0f, 20.0f);
	title.setFont(font);
}

void MapMenuState::initBackground()
{
	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
	background.setFillColor(sf::Color(0, 0, 80, 255));
}

sf::Vector2f MapMenuState::calculateScreenCenter() const
{
	return sf::Vector2f(window->getSize()) / 2.0f;
}

sf::Vector2f MapMenuState::calculateMapGridPosition() const
{
	sf::Vector2f center = calculateScreenCenter();
	sf::Vector2f layout_dimensions;
	layout_dimensions.x = MAP_BUTTON_DIMENSIONS.x * GRID_LAYOUT_COLUMNS + MAP_BUTTON_SPACE * (GRID_LAYOUT_COLUMNS - 1);
	size_t grid_layout_rows = MAPS_COUNT / GRID_LAYOUT_COLUMNS;
	layout_dimensions.y = MAP_BUTTON_DIMENSIONS.y * grid_layout_rows + MAP_BUTTON_SPACE * (grid_layout_rows - 1);

	sf::Vector2f position = center - (layout_dimensions / 2.0f);
	return position;
}

MapMenuState::~MapMenuState()
{

}

void MapMenuState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleExitEvent(event);
		handleControlsEvent(event);
	}
}

void MapMenuState::handleExitEvent(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window->close();
	}
}

void MapMenuState::handleControlsEvent(sf::Event& event)
{
	grid_layout.handleEvent(event);
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void MapMenuState::update(float deltaSeconds)
{
	updateControls(deltaSeconds);
}

void MapMenuState::updateControls(float deltaSeconds)
{
	grid_layout.update(deltaSeconds);
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(deltaSeconds);
	}
}

void MapMenuState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);
	window->draw(title);
	drawControls(window);
	window->display();
}

void MapMenuState::drawControls(std::shared_ptr<sf::RenderWindow> window)
{
	grid_layout.draw(window);
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}
