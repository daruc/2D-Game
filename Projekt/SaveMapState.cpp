#include <iostream>
#include <fstream>
#include "Map.h"
#include "SaveMapState.h"
#include "TextField.h"
#include "Button.h"
#include "EditorState.h"
#include "Strings.h"

SaveMapState::SaveMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window)
{
	float center_x = window->getSize().x / 2;
	float center_y = window->getSize().y / 2;
	Strings* strings = Strings::Instance();
	this->map = map;
	std::shared_ptr<TextField> text_field = std::make_shared<TextField>(window);
	text_field->setCoordinates(center_x - 180.0f, center_y - 20.0f);
	text_field->setDimensions(300.0f, 40.0f);
	controls.push_back(text_field);

	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, strings->getSave());
	save_button->setCoordinates(center_x + 130.0f, center_y - 20.0f);
	save_button->setDimensions(100.0f, 40.0f);
	save_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;
		save(text_field->getString());
	});
	controls.push_back(save_button);

	std::shared_ptr<Button> editor_button = std::make_shared<Button>(window, strings->getEditor());
	editor_button->setCoordinates(20.0f, 20.0f);
	editor_button->setDimensions(130.0f, 40.0f);
	editor_button->addListener([this](std::string str)->void {
		State::nextState = std::make_shared<EditorState>(State::window, this->map);
	});
	controls.push_back(editor_button);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->getSaveMapTitle());
	title.setPosition(180.0f, 20.0f);
	title.setFont(font);

	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
	background.setFillColor(sf::Color(0, 0, 80, 255));
}

SaveMapState::~SaveMapState()
{

}

void SaveMapState::handleEvents()
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

void SaveMapState::update()
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update();
	}
}

void SaveMapState::draw()
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

void SaveMapState::save(sf::String filename)
{
	std::ofstream fout;
	fout.open(filename.toAnsiString().c_str(), std::fstream::out | std::fstream::binary | std::fstream::trunc);
	std::pair<int, char*> bytes = map->toBinary();
	fout.write(bytes.second, bytes.first);
	delete[] bytes.second;
	fout.close();
}