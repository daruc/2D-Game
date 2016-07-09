#include <iostream>
#include <fstream>
#include "ControlsState.h"
#include "KeyField.h"
#include "Button.h"
#include "MainManuState.h"
#include "Strings.h"

ControlsState::ControlsState(std::shared_ptr<sf::RenderWindow> window)
	: State(window)
{
	float center = window->getSize().x / 2;
	Strings* strings = Strings::Instance();
	std::shared_ptr<Button> back = std::make_shared<Button>(window, strings->getMainMenu());
	back->setCoordinates(20.0f, 20.0f);
	back->setDimensions(200.0f, 40.0f);
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(back);

	std::tuple<sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key> keys;
	keys = load();

	left_field = std::make_shared<KeyField>(window, std::get<0>(keys));
	left_field->setDimensions(120.0f, 40.0f);
	left_field->setCoordinates(center - 60.0f, 100.0f);
	left_field->setDescription(strings->getTurnLeft());
	controls.push_back(left_field);

	right_field = std::make_shared<KeyField>(window, std::get<1>(keys));
	right_field->setDimensions(120.0f, 40.0f);
	right_field->setCoordinates(center - 60.0f, 150.0f);
	right_field->setDescription(strings->getTurnRight());
	controls.push_back(right_field);

	crouch_field = std::make_shared<KeyField>(window, std::get<2>(keys));
	crouch_field->setDimensions(120.0f, 40.0f);
	crouch_field->setCoordinates(center - 60.0f, 200.0f);
	crouch_field->setDescription(strings->getCrouch());
	controls.push_back(crouch_field);

	jump_field = std::make_shared<KeyField>(window, std::get<3>(keys));
	jump_field->setDimensions(120.0f, 40.0f);
	jump_field->setCoordinates(center - 60.0f, 250.0f);
	jump_field->setDescription(strings->getJump());
	controls.push_back(jump_field);

	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, strings->getSave());
	save_button->setDimensions(100.0f, 40.0f);
	save_button->setCoordinates(center - 50.0f, 400.0f);
	save_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		save();
	});
	controls.push_back(save_button);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	title.setString(strings->getControlsTitle());
	title.setPosition(250.0f, 20.0f);
	title.setFont(font);

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

void ControlsState::update()
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update();
	}
}

void ControlsState::draw()
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