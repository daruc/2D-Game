#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
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
	textures.loadTick();

	for (int i = 0; i < 18; ++i)
	{
		tick[i].setTexture(*textures.getTick());
	}

	std::fstream fin;
	fin.open(L"maps.bin", std::fstream::in);

	for (int i = 0; i < 18; ++i)
	{
		fin >> completed[i];
	}

	Strings* strings = Strings::Instance();

	sf::Vector2u resolution = window->getSize();
	float width = 100.0f * 6.0f + 20.0f * 5.0f;
	float height = 100.0f * 3.0f + 20.0f * 2.0f;
	float left = (resolution.x / 2.0f) - (width / 2.0f);
	float top = (resolution.y / 2.0f) - (height / 2.0f);
	float x, y;

	for (int i = 0; i < 18; ++i)
	{
		std::stringstream str;
		str << "map_" << (i + 1);
		std::shared_ptr<Button> map_button = std::make_shared<Button>(window, strings->get(str.str().c_str()));

		if (i < 6) { x = left + 120.0f * i; y = top; }
		else if (i < 12) { x = left + 120.0f * (i - 6); y = top + 120.0f; }
		else { x = left + 120.0f * (i - 12); y = top + 240.0f; }

		map_button->setCoordinates(x, y);
		x = x + 100.0f - 36.0f;
		y = y + 100.0f - 36.0f;
		tick[i].setPosition(x, y);

		map_button->setDimensions(100.0f, 100.0f);
		map_button->addListener([this](std::string str)->void {
			std::cout << "Mapa 1\n";

			MapBuilder mapBuilder;
			mapBuilder.loadFromFile(L"maps\\map_1");
			std::shared_ptr<Map> map = mapBuilder.get();
			State::nextState = std::make_shared<GameState>(State::window, map);
		});
		controls.push_back(map_button);
		
	}

	std::shared_ptr<Button> back = std::make_shared<Button>(window, strings->get("main_menu"));
	back->setCoordinates(20.0f, 20.0f);
	back->setDimensions(200.0f, 40.0f);
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(back);

	std::shared_ptr<TextField> text_field = std::make_shared<TextField>(window);
	text_field->setCoordinates( (resolution.x/2.0f) - 200.0f, resolution.y - 60.0f);
	text_field->setDimensions(250.0f, 40.0f);
	controls.push_back(text_field);

	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->get("load"));
	load_button->setCoordinates((resolution.x / 2.0f) - 200.0f + 270.0f, resolution.y - 60.0f);
	load_button->setDimensions(130.0f, 40.0f);
	load_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;

		std::wstringstream sstream;
		sstream << "user_maps\\" << text_field->getString().toWideString();

		MapBuilder mapBuilder;
		bool exist = mapBuilder.loadFromFile(sstream.str());
		if (exist)
		{
			std::shared_ptr<Map> map = mapBuilder.get();
			State::nextState = std::make_shared<GameState>(State::window, map);
		}
	});
	controls.push_back(load_button);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->get("map_menu_title"));
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

void MapMenuState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);

	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw(window);
	}

	for (int i = 0; i < 18; ++i)
	{
		if (completed[i])
		{
			window->draw(tick[i]);
		}
	}
	
	window->draw(title);
	window->display();
}