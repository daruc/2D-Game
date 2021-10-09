#include <iostream>
#include <memory>
#include <sstream>

#include "GUI/Button.h"
#include "MapMenuState.h"
#include "GameOverState.h"
#include "Strings.h"


GameOverState::GameOverState(std::shared_ptr<sf::RenderWindow> window, bool isWin, float seconds)
	: State(window)
{
	Strings* strings = Strings::Instance();
	std::shared_ptr<Button> back = std::make_shared<Button>(window, strings->get("new_game"));
	back->setCoordinates(20.0f, 20.0f);
	back->setDimensions(200.0f, 40.0f);
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MapMenuState>(State::window);
	});
	controls.push_back(back);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	if (isWin)
	{
		title.setString(strings->get("win"));
		if (!sound_buffer.loadFromFile("sounds\\victory.wav"))
		{
			std::cout << "Cannot load sound victory.wav\n";
		}


		std::wstringstream stream;
		stream.precision(1);
		stream << std::fixed;
		stream << strings->get("your_time") << ": " << seconds << " " << strings->get("seconds");
		time.setString(stream.str());
	}
	else
	{
		title.setString(strings->get("defeat"));
		if (!sound_buffer.loadFromFile("sounds\\game_over.wav"))
		{
			std::cout << "Cannot load sound game_over.wav\n";
		}
	}
	sound.setBuffer(sound_buffer);
	title.setPosition(250.0f, 20.0f);
	title.setFont(font);
	time.setFont(font);
	time.setPosition(window->getSize().x / 2 - 100.0f, window->getSize().y / 2 - 15.0f);

	background.setSize(sf::Vector2f(window->getSize().x, 80.0f));
	background.setFillColor(sf::Color(0, 0, 80, 255));
	sound.play();
}

GameOverState::~GameOverState()
{

}

void GameOverState::handleEvents()
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
void GameOverState::update(float deltaSeconds)
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update(deltaSeconds);
	}
}

void GameOverState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(sf::Color(0, 0, 100, 255));
	window->draw(background);

	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw(window);
	}

	window->draw(title);
	window->draw(time);
	window->display();
}