#include <iostream>
#include <fstream>
#include "LoadMapState.h"
#include "TextField.h"
#include "Button.h"
#include "Map.h"
#include "EditorState.h"
#include "Strings.h"

LoadMapState::LoadMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window)
{
	Strings* strings = Strings::Instance();
	prev_map = map;
	std::shared_ptr<TextField> text_field = std::make_shared<TextField>(window);
	text_field->setCoordinates(150.0f, 300.0f);
	text_field->setDimensions(300.0f, 40.0f);
	controls.push_back(text_field);

	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->getLoad());
	load_button->setCoordinates(470.0f, 300.0f);
	load_button->setDimensions(100.0f, 40.0f);
	load_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;
		std::ifstream fin;
		fin.open(text_field->getString().toAnsiString(), std::fstream::out | std::fstream::binary);
		if (!fin.is_open())
		{
			std::cout << "Cannot open file.\n";
		}
		else
		{
			fin.seekg(0, fin.end);
			int length = fin.tellg();
			fin.seekg(0, fin.beg);

			char * buffer = new char[length];

			fin.read(buffer, length);
			std::shared_ptr<Map> map = std::make_shared<Map>();
			map->fromBinary(length, buffer);
			this->State::nextState = std::make_shared<EditorState>(window, map);
			delete[] buffer;
		}		
	});
	controls.push_back(load_button);

	std::shared_ptr<Button> editor_button = std::make_shared<Button>(window, strings->getEditor());
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

	title.setString(strings->getLoadMapTitle());
	title.setPosition(180.0f, 20.0f);
	title.setFont(font);

	background.setSize(sf::Vector2f(800.0f, 80.0f));
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
void LoadMapState::update()
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update();
	}
}
void LoadMapState::draw()
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