#include <iostream>
#include <fstream>
#include "Map.h"
#include "SaveMapState.h"
#include "TextField.h"
#include "Button.h"
#include "EditorState.h"

SaveMapState::SaveMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window)
{
	this->map = map;
	std::shared_ptr<TextField> text_field = std::make_shared<TextField>(window);
	text_field->setCoordinates(150.0f, 300.0f);
	text_field->setDimensions(300.0f, 40.0f);
	controls.push_back(text_field);

	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, "Zapisz");
	save_button->setCoordinates(470.0f, 300.0f);
	save_button->setDimensions(100.0f, 40.0f);
	save_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;
		save(text_field->getString());
	});
	controls.push_back(save_button);

	std::shared_ptr<Button> editor_button = std::make_shared<Button>(window, "Edytor");
	editor_button->setCoordinates(20.0f, 20.0f);
	editor_button->setDimensions(130.0f, 40.0f);
	editor_button->addListener([this](std::string str)->void {
		State::nextState = std::make_shared<EditorState>(State::window, this->map);
	});
	controls.push_back(editor_button);
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
	window->clear();
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw();
	}
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