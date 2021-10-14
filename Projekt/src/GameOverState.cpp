#include <iostream>
#include <memory>
#include <sstream>

#include "GUI/Button.h"
#include "MapMenuState.h"
#include "GameOverState.h"
#include "Strings.h"


namespace {
	sf::Color BACKGROUND_COLOR(0, 0, 100, 255);
}


GameOverState::GameOverState(std::shared_ptr<sf::RenderWindow> window, bool isWin, float seconds)
	: State(window)
{
	Strings* strings = Strings::Instance();
	createBackButton(strings);

	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font from file.\n";
	}

	if (isWin)
	{
		initWin(strings, seconds);
	}
	else
	{
		initDefeated(strings);
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

void GameOverState::initWin(Strings* strings, float seconds)
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

void GameOverState::initDefeated(Strings* strings)
{
	title.setString(strings->get("defeat"));
	if (!sound_buffer.loadFromFile("sounds\\game_over.wav"))
	{
		std::cout << "Cannot load sound game_over.wav\n";
	}
}

void GameOverState::createBackButton(Strings* strings)
{
	std::shared_ptr<Button> back = std::make_shared<Button>(window, strings->get("new_game"));
	back->setPosition(sf::Vector2f(20.0f, 20.0f));
	back->setDimensions(sf::Vector2f(200.0f, 40.0f));
	back->addListener([this](std::string str)->void {
		std::cout << "back\n";
		State::nextState = std::make_shared<MapMenuState>(State::window);
	});
	controls.push_back(back);
}

GameOverState::~GameOverState()
{

}

void GameOverState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleExitEvent(event);
		handleControlsEvents(event);
	}
}

void GameOverState::handleExitEvent(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		window->close();
	}
}

void GameOverState::handleControlsEvents(sf::Event& event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void GameOverState::update(float deltaSeconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(deltaSeconds);
	}
}

void GameOverState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear(BACKGROUND_COLOR);
	window->draw(background);
	drawControls(window);
	window->draw(title);
	window->draw(time);
	window->display();
}

void GameOverState::drawControls(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}