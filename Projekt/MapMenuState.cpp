#include <memory>
#include <iostream>
#include <fstream>
#include "MapMenuState.h"
#include "MainManuState.h"
#include "GameState.h"
#include "TextField.h"
#include "Button.h"
#include "Map.h"
#include "Strings.h"
#include "MapBuilder.h"


MapMenuState::MapMenuState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	Strings* strings = Strings::Instance();
	std::shared_ptr<Button> map_1 = std::make_shared<Button>(window, strings->getMap1());
	map_1->setCoordinates(300.0f, 100.0f);
	map_1->setDimensions(100.0f, 100.0f);
	map_1->addListener([this](std::string str)->void {
		std::cout << "Mapa 1\n";

		MapBuilder mapBuilder;
		mapBuilder.loadFromFile(L"Mapa 1");
		std::shared_ptr<Map> map = mapBuilder.get();
		State::nextState = std::make_shared<GameState>(State::window, map);
	});
	controls.push_back(map_1);

	std::shared_ptr<Button> map_2 = std::make_shared<Button>(window, strings->getMap2());
	map_2->setCoordinates(500.0f, 100.0f);
	map_2->setDimensions(100.0f, 100.0f);
	map_2->addListener([this](std::string str)->void {
		std::cout << "Mapa 2\n";

		MapBuilder mapBuilder;
		mapBuilder.loadFromFile(L"Mapa 2");
		std::shared_ptr<Map> map = mapBuilder.get();
		State::nextState = std::make_shared<GameState>(State::window, map);
	});
	controls.push_back(map_2);

	std::shared_ptr<Button> map_3 = std::make_shared<Button>(window, strings->getMap3());
	map_3->setCoordinates(300.0f, 300.0f);
	map_3->setDimensions(100.0f, 100.0f);
	map_3->addListener([this](std::string str)->void {
		std::cout << "Mapa 3\n";

		MapBuilder mapBuilder;
		mapBuilder.loadFromFile(L"Mapa 3");
		std::shared_ptr<Map> map = mapBuilder.get();
		State::nextState = std::make_shared<GameState>(State::window, map);
	});
	controls.push_back(map_3);

	std::shared_ptr<Button> map_4 = std::make_shared<Button>(window, strings->getMap4());
	map_4->setCoordinates(500.0f, 300.0f);
	map_4->setDimensions(100.0f, 100.0f);
	map_4->addListener([this](std::string str)->void {
		std::cout << "Mapa 4\n";

		MapBuilder mapBuilder;
		mapBuilder.loadFromFile(L"Mapa 4");
		std::shared_ptr<Map> map = mapBuilder.get();
		State::nextState = std::make_shared<GameState>(State::window, map);
	});
	controls.push_back(map_4);

	std::shared_ptr<Button> back = std::make_shared<Button>(window, strings->getMainMenu());
	back->setCoordinates(20.0f, 20.0f);
	back->setDimensions(200.0f, 40.0f);
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(back);

	std::shared_ptr<TextField> text_field = std::make_shared<TextField>(window);
	text_field->setCoordinates(300.0f, 500.0f);
	text_field->setDimensions(200.0f, 40.0f);
	controls.push_back(text_field);

	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->getLoad());
	load_button->setCoordinates(520.0f, 500.0f);
	load_button->setDimensions(130.0f, 40.0f);
	load_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;

		MapBuilder mapBuilder;
		mapBuilder.loadFromFile(text_field->getString().toWideString());
		std::shared_ptr<Map> map = mapBuilder.get();
		State::nextState = std::make_shared<GameState>(State::window, map);
	});
	controls.push_back(load_button);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->getMapMenuTitle());
	title.setPosition(250.0f, 20.0f);
	title.setFont(font);

	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
	background.setFillColor(sf::Color(0, 0, 80, 255));
}

MapMenuState::~MapMenuState()
{

}

void MapMenuState::handleEvents()
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

void MapMenuState::update()
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update();
	}
}

void MapMenuState::draw()
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