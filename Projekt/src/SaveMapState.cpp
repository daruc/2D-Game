#include <iostream>
#include <fstream>
#include <thread>

#include "Map.h"
#include "SaveMapState.h"
#include "GUI/TextField.h"
#include "GUI/Button.h"
#include "Editor/EditorState.h"
#include "Strings.h"


SaveMapState::SaveMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window)
{
	Strings* strings = Strings::Instance();
	this->map = map;

	createTextField(window);
	createSaveButton(window, strings);
	createEditorButton(window, strings);
	initTitle(strings);
	initBackground(window);
}

sf::Vector2f SaveMapState::getScreenCenter(std::shared_ptr<sf::RenderWindow> window) const
{
	return sf::Vector2f(window->getSize()) / 2.0f;
}

void SaveMapState::createTextField(std::shared_ptr<sf::RenderWindow> window)
{
	sf::Vector2f centerOffset(-180.0f, -20.0f);

	text_field = std::make_shared<TextField>(window);
	text_field->setPosition(getScreenCenter(window) + centerOffset);
	text_field->setDimensions(300.0f, 40.0f);
	controls.push_back(text_field);
}

void SaveMapState::createSaveButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	sf::Vector2f centerOffset(130.0f, -20.0f);

	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, strings->get("save"));
	save_button->setPosition(getScreenCenter(window) + centerOffset);
	save_button->setDimensions(sf::Vector2f(100.0f, 40.0f));
	save_button->addListener([=](std::string str)->void {
		std::cout << "click " << str << std::endl;
		save(text_field->getString());
	});
	controls.push_back(save_button);
}

void SaveMapState::createEditorButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings)
{
	std::shared_ptr<Button> editor_button = std::make_shared<Button>(window, strings->get("editor"));
	editor_button->setPosition(sf::Vector2f(20.0f, 20.0f));
	editor_button->setDimensions(sf::Vector2f(130.0f, 40.0f));
	editor_button->addListener([this](std::string str)->void {
		State::nextState = std::make_shared<EditorState>(State::window, this->map);
	});
	controls.push_back(editor_button);
}

void SaveMapState::initTitle(Strings* strings)
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->get("save_map_title"));
	title.setPosition(180.0f, 20.0f);
	title.setFont(font);
}

void SaveMapState::initBackground(std::shared_ptr<sf::RenderWindow> window)
{
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
		handleExitEvent(event);
		handleControlsEvents(event);
	}
}

void SaveMapState::handleExitEvent(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window->close();
	}
}

void SaveMapState::handleControlsEvents(sf::Event& event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void SaveMapState::update(float delta_seconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(delta_seconds);
	}
}

void SaveMapState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);
	drawControls(window);
	window->draw(title);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void SaveMapState::drawControls(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}

void SaveMapState::save(sf::String filename)
{
	std::ofstream fout;
	fout.open(filename.toAnsiString().c_str(), std::fstream::out | std::fstream::binary | std::fstream::trunc);
	std::vector<char> bytes = map->toBinary();
	fout.write(bytes.data(), bytes.size());
	fout.close();
}