#include <iostream>
#include <fstream>
#include <thread>

#include "GUI/KeyField.h"
#include "GUI/Button.h"

#include "ControlsState.h"
#include "MainManuState.h"
#include "Strings.h"


ControlsState::ControlsState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	float center = window->getSize().x / 2;
	Strings* strings = Strings::Instance();
	initBack(window, strings);

	std::tuple<sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key> keys = load();

	initLeftField(window, keys, center, strings);
	initRightField(window, keys, center, strings);
	initCrouchField(window, keys, center, strings);
	initJumpField(window, keys, center, strings);
	initSaveButton(window, center, strings);
	loadFont();
	initTitle(strings);
	initBackground(window);
}

void ControlsState::initBack(std::shared_ptr<sf::RenderWindow>& window, Strings* strings)
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

void ControlsState::initRightField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center, Strings* strings)
{
	right_field = std::make_shared<KeyField>(window, std::get<1>(keys));
	right_field->setDimensions(120.0f, 40.0f);
	right_field->setPosition(sf::Vector2f(center - 60.0f, 150.0f));
	right_field->setDescription(strings->get("turn_right"));
	controls.push_back(right_field);
}

void ControlsState::initLeftField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center,
	Strings* strings)
{
	left_field = std::make_shared<KeyField>(window, std::get<0>(keys));
	left_field->setDimensions(120.0f, 40.0f);
	left_field->setPosition(sf::Vector2f(center - 60.0f, 100.0f));
	left_field->setDescription(strings->get("turn_left"));
	controls.push_back(left_field);
}

void ControlsState::initCrouchField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center, Strings* strings)
{
	crouch_field = std::make_shared<KeyField>(window, std::get<2>(keys));
	crouch_field->setDimensions(120.0f, 40.0f);
	crouch_field->setPosition(sf::Vector2f(center - 60.0f, 200.0f));
	crouch_field->setDescription(strings->get("crouch"));
	controls.push_back(crouch_field);
}

void ControlsState::initJumpField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center, Strings* strings)
{
	jump_field = std::make_shared<KeyField>(window, std::get<3>(keys));
	jump_field->setDimensions(120.0f, 40.0f);
	jump_field->setPosition(sf::Vector2f(center - 60.0f, 250.0f));
	jump_field->setDescription(strings->get("jump"));
	controls.push_back(jump_field);
}

void ControlsState::initSaveButton(std::shared_ptr<sf::RenderWindow>& window, float center, Strings* strings)
{
	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, strings->get("save"));
	save_button->setDimensions(sf::Vector2f(100.0f, 40.0f));
	save_button->setPosition(sf::Vector2f(center - 50.0f, 400.0f));
	save_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		save();
	});
	controls.push_back(save_button);
}

void ControlsState::loadFont()
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}
}

void ControlsState::initTitle(Strings* strings)
{
	title.setString(strings->get("controls_title"));
	title.setPosition(250.0f, 20.0f);
	title.setFont(font);
}

void ControlsState::initBackground(std::shared_ptr<sf::RenderWindow>& window)
{
	background.setFillColor(sf::Color(0, 0, 80, 255));
	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
}


std::tuple<sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key>
	ControlsState::load()
{
	std::ifstream fin;
	fin.open("controls.bin", std::fstream::binary | std::fstream::in);
	if (!fin.is_open())
	{
		std::cout << "Cannot open controls.bin file.\n";
	}

	char buffer[16];
	fin.read(buffer, 16);
	int left, right, crouch, jump;
	memcpy(&left, buffer, 4);
	memcpy(&right, buffer + 4, 4);
	memcpy(&crouch, buffer + 8, 4);
	memcpy(&jump, buffer + 12, 4);

	return std::make_tuple(static_cast<sf::Keyboard::Key> (left),
		static_cast<sf::Keyboard::Key> (right),
		static_cast<sf::Keyboard::Key> (crouch),
		static_cast<sf::Keyboard::Key> (jump));
}

void ControlsState::save()
{
	std::ofstream fout;
	fout.open("controls.bin", std::fstream::out | std::fstream::binary | std::fstream::trunc);
	if (!fout.is_open())
	{
		std::cout << "Cannot open controls.bin file.\n";
	}

	int key = (int) left_field->getKey();
	char bytes[4];
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	key = (int) right_field->getKey();
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	key = (int) crouch_field->getKey();
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	key = (int)jump_field->getKey();
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	fout.close();
}

ControlsState::~ControlsState()
{

}

void ControlsState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleExitEvent(event);
		handleControlsEvent(event);
	}
}

void ControlsState::handleExitEvent(sf::Event & event)
{
	if (event.type == sf::Event::Closed)
	{
		window->close();
	}
}

void ControlsState::handleControlsEvent(sf::Event event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void ControlsState::update(float delta_seconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(delta_seconds);
	}
}

void ControlsState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);
	drawControls(window);
	window->draw(title);
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void ControlsState::drawControls(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}