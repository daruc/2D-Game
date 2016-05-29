#include <memory>
#include <iostream>
#include "MapMenuState.h"
#include "MainManuState.h"
#include "TextField.h"
#include "Button.h"

MapMenuState::MapMenuState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	std::shared_ptr<Button> map_1 = std::make_shared<Button>(window, "Mapa 1");
	map_1->setCoordinates(300.0f, 100.0f);
	map_1->setDimensions(100.0f, 100.0f);
	map_1->addListener([this](std::string str)->void {
		std::cout << "Mapa 1\n";
	});
	controls.push_back(map_1);

	std::shared_ptr<Button> map_2 = std::make_shared<Button>(window, "Mapa 2");
	map_2->setCoordinates(500.0f, 100.0f);
	map_2->setDimensions(100.0f, 100.0f);
	map_2->addListener([this](std::string str)->void {
		std::cout << "Mapa 2\n";
	});
	controls.push_back(map_2);

	std::shared_ptr<Button> map_3 = std::make_shared<Button>(window, "Mapa 3");
	map_3->setCoordinates(300.0f, 300.0f);
	map_3->setDimensions(100.0f, 100.0f);
	map_3->addListener([this](std::string str)->void {
		std::cout << "Mapa 3\n";
	});
	controls.push_back(map_3);

	std::shared_ptr<Button> map_4 = std::make_shared<Button>(window, "Mapa 4");
	map_4->setCoordinates(500.0f, 300.0f);
	map_4->setDimensions(100.0f, 100.0f);
	map_4->addListener([this](std::string str)->void {
		std::cout << "Mapa 4\n";
	});
	controls.push_back(map_4);

	std::shared_ptr<Button> back = std::make_shared<Button>(window, "Menu g³ówne\n");
	back->setCoordinates(20.0f, 20.0f);
	back->setDimensions(80.0f, 40.0f);
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(back);

	std::shared_ptr<TextField> text_field = std::make_shared<TextField>(window);
	text_field->setCoordinates(500.0f, 500.0f);
	text_field->setDimensions(100.0f, 40.0f);
	controls.push_back(text_field);
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
	window->clear();

	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw();
	}

	window->display();
}