#include <memory>
#include <iostream>
#include "EditorState.h"
#include "Button.h"
#include "MainManuState.h"
#include "SaveMapState.h"
#include "LoadMapState.h"

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window)
	: State(window), view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y))
{
	selected = GROUND;
	std::shared_ptr<Button> menu_button = std::make_shared<Button>(window, "Menu");
	menu_button->setCoordinates(0.0f, 0.0f);
	menu_button->setDimensions(130.0f, 40.0f);
	menu_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(menu_button);

	std::shared_ptr<Button> back_button = std::make_shared<Button>(window, "Cofnij");
	back_button->setCoordinates(0.0f, 45.0f);
	back_button->setDimensions(130.0f, 40.0f);
	back_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;

		if (points.size() > 0)
		{
			points.pop_back();
		}
		else
		{
			map->removeLast();
		}
	});
	controls.push_back(back_button);

	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, "Zapisz");
	save_button->setCoordinates(0.0f, 90.0f);
	save_button->setDimensions(130.0f, 40.0f);
	save_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<SaveMapState>(State::window, map);
	});
	controls.push_back(save_button);

	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, "Wczytaj");
	load_button->setCoordinates(0.0f, 135.f);
	load_button->setDimensions(130.0f, 40.0f);
	load_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<LoadMapState>(State::window);
	});
	controls.push_back(load_button);

	std::shared_ptr<Button> begin_button = std::make_shared<Button>(window, "Pocz¹tek");
	begin_button->setCoordinates(0.0f, 180.0f);
	begin_button->setDimensions(130.0f, 40.0f);
	begin_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = PLAYER;
	});
	controls.push_back(begin_button);

	std::shared_ptr<Button> finish_button = std::make_shared<Button>(window, "Koniec");
	finish_button->setCoordinates(0.0f, 225.0f);
	finish_button->setDimensions(130.0f, 40.0f);
	finish_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = FINISH;
	});
	controls.push_back(finish_button);

	std::shared_ptr<Button> ground_button = std::make_shared<Button>(window, "Ziemia");
	ground_button->setCoordinates(0.0f, 270.0f);
	ground_button->setDimensions(130.0f, 40.0f);
	ground_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = GROUND;
	});
	controls.push_back(ground_button);

	std::shared_ptr<Button> enemy_button = std::make_shared<Button>(window, "Przeciwnik");
	enemy_button->setCoordinates(0.0f, 315.0f);
	enemy_button->setDimensions(130.0f, 40.0);
	enemy_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = ENEMY;
	});
	controls.push_back(enemy_button);

	std::shared_ptr<Button> type1_button = std::make_shared<Button>(window, "Typ 1");
	type1_button->setCoordinates(0.0f, 360.0f);
	type1_button->setDimensions(130.0f, 40.0f);
	type1_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
	});
	controls.push_back(type1_button);

	std::shared_ptr<Button> type2_button = std::make_shared<Button>(window, "Typ 2");
	type2_button->setCoordinates(0.0f, 405.0f);
	type2_button->setDimensions(130.0f, 40.0f);
	type2_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
	});
	controls.push_back(type2_button);

	std::shared_ptr<Button> type3_button = std::make_shared<Button>(window, "Typ 3");
	type3_button->setCoordinates(0.0f, 450.0f);
	type3_button->setDimensions(130.0f, 40.0f);
	type3_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
	});
	controls.push_back(type3_button);

	std::shared_ptr<Button> type4_button = std::make_shared<Button>(window, "Typ 4");
	type4_button->setCoordinates(0.0f, 495.0f);
	type4_button->setDimensions(130.0f, 40.0f);
	type4_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
	});
	controls.push_back(type4_button);

	map = std::make_shared<Map>();

	background.setSize(sf::Vector2f(130.0, 600.0f));
	background.setFillColor(sf::Color::White);

	start.setRadius(30.0f);
	start.setFillColor(sf::Color::Green);
	start.setPosition(map->getPlayerPosition());
	finish.setRadius(30.0f);
	finish.setFillColor(sf::Color::Red);
	finish.setPosition(map->getFinishPosition());
}

EditorState::~EditorState()
{

}

void EditorState::moveAllPoints(float x, float y)
{
	auto begin = points.begin();
	auto end = points.end();
	for (auto it = begin; it != end; ++it)
	{
		it->x += x;
		it->y += y;
	}
}

void EditorState::handleMouseModeGround(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i coor = sf::Mouse::getPosition(*State::window);
			std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
			if (coor.x > 130)
			{
				points.push_back(sf::Vector2f(coor.x - 1, coor.y - 1));
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			if (points.size() >= 3)
			{
				map->addShape(points);
				points.clear();
			}
		}
	}
}

void EditorState::handleMouseModePlayer(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i coor = sf::Mouse::getPosition(*State::window);
			std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
			if (coor.x > 130)
			{
				map->setPlayerPosition(coor.x, coor.y);

				sf::Vector2f new_coor = map->getPlayerPosition();
				start.setPosition(new_coor.x, new_coor.y);
			}
		}
	}
}

void EditorState::handleMouseModeFinish(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i coor = sf::Mouse::getPosition(*State::window);
			std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
			if (coor.x > 130)
			{
				map->setFinishPosition(coor.x, coor.y);

				sf::Vector2f new_coor = map->getFinishPosition();
				finish.setPosition(new_coor.x, new_coor.y);
			}
		}
	}
}

void EditorState::handleMouse(sf::Event & event)
{
	switch (selected)
	{
	case GROUND:
		handleMouseModeGround(event);
		break;
	case PLAYER:
		handleMouseModePlayer(event);
		break;
	case FINISH:
		handleMouseModeFinish(event);
		break;
	}
	
}

void EditorState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else {
			auto begin = controls.begin();
			auto end = controls.end();
			for (auto it = begin; it != end; ++it)
			{
				(*it)->handleEvents(event);
			}
			handleMouse(event);

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
					view.move(50.0f, 0.0f);
					map->moveView(sf::Vector2f(50.0f, 0.0f));
					moveAllPoints(-50.0f, 0.0f);
					std::cout << "view.move right\n";
					break;
				case sf::Keyboard::Left:
					view.move(-50.0f, 0.0f);
					map->moveView(sf::Vector2f(-50.0f, 0.0f));
					moveAllPoints(50.0f, 0.0f);
					std::cout << "view.move left\n";
					break;
				case sf::Keyboard::Down:
					view.move(0.0f, 50.0f);
					map->moveView(sf::Vector2f(0.0f, 50.0f));
					moveAllPoints(0.0f, -50.0f);
					std::cout << "view.move down\n";
					break;
				case sf::Keyboard::Up:
					view.move(0.0f, -50.0f);
					map->moveView(sf::Vector2f(0.0f, -50.0f));
					moveAllPoints(0.0f, 50.0f);
					std::cout << "view.move up\n";
					break;
				}
			}
		}
	}
}

void EditorState::update()
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update();
	}
}

void EditorState::draw()
{
	State::window->clear();

	//points
	std::list<sf::Vector2f>::iterator begin2 = points.begin();
	std::list<sf::Vector2f>::iterator end2 = points.end();
	sf::RectangleShape point;
	point.setFillColor(sf::Color::Green);
	point.setSize(sf::Vector2f(3.0f, 3.0f));
	for (std::list<sf::Vector2f>::iterator it2 = begin2; it2 != end2; ++it2)
	{
		point.setPosition(*it2);
		window->draw(point);
	}

	//map
	window->setView(view);
	map->draw(*window);
	window->draw(start);
	window->draw(finish);
	window->setView(window->getDefaultView());

	window->draw(background);
	//GUI
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw();
	}

	window->display();
}