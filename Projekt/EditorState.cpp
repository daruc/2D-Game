#include <memory>
#include <iostream>
#include "EditorState.h"
#include "Button.h"
#include "MainManuState.h"
#include "SaveMapState.h"
#include "LoadMapState.h"
#include "Strings.h"

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window)
	: State(window), view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y))
{
	Strings* strings = Strings::Instance();
	selected = GROUND;
	std::shared_ptr<Button> menu_button = std::make_shared<Button>(window, strings->get("menu"));
	menu_button->setCoordinates(0.0f, 0.0f);
	menu_button->setDimensions(130.0f, 40.0f);
	menu_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(menu_button);

	std::shared_ptr<Button> back_button = std::make_shared<Button>(window, strings->get("undo"));
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

	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, strings->get("save"));
	save_button->setCoordinates(0.0f, 90.0f);
	save_button->setDimensions(130.0f, 40.0f);
	save_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<SaveMapState>(State::window, map);
	});
	controls.push_back(save_button);

	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->get("load"));
	load_button->setCoordinates(0.0f, 135.f);
	load_button->setDimensions(130.0f, 40.0f);
	load_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<LoadMapState>(State::window, map);
	});
	controls.push_back(load_button);

	std::shared_ptr<Button> begin_button = std::make_shared<Button>(window, strings->get("player"));
	begin_button->setCoordinates(0.0f, 180.0f);
	begin_button->setDimensions(130.0f, 40.0f);
	begin_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = PLAYER;
	});
	controls.push_back(begin_button);

	std::shared_ptr<Button> finish_button = std::make_shared<Button>(window, strings->get("finish"));
	finish_button->setCoordinates(0.0f, 225.0f);
	finish_button->setDimensions(130.0f, 40.0f);
	finish_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = FINISH;
	});
	controls.push_back(finish_button);

	std::shared_ptr<Button> ground_button = std::make_shared<Button>(window, strings->get("ground"));
	ground_button->setCoordinates(0.0f, 270.0f);
	ground_button->setDimensions(130.0f, 40.0f);
	ground_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = GROUND;
	});
	controls.push_back(ground_button);

	std::shared_ptr<Button> fire_button = std::make_shared<Button>(window, strings->get("fire"));
	fire_button->setCoordinates(0.0f, 315.0f);
	fire_button->setDimensions(130.0f, 40.0f);
	fire_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = FIRE;

		points.clear();
	});
	controls.push_back(fire_button);

	std::shared_ptr<Button> enemy_button = std::make_shared<Button>(window, strings->get("enemy"));
	enemy_button->setCoordinates(0.0f, 360.0f);
	enemy_button->setDimensions(130.0f, 40.0);
	enemy_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected = ENEMY;
	});
	controls.push_back(enemy_button);

	std::shared_ptr<Button> type1_button = std::make_shared<Button>(window, strings->get("type_1"));
	type1_button->setCoordinates(0.0f, 405.0f);
	type1_button->setDimensions(130.0f, 40.0f);
	type1_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected_type.setPosition(110.0f, 405.0f);
		map->setType(1);
		textures.loadMapType(1);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type1_button);

	std::shared_ptr<Button> type2_button = std::make_shared<Button>(window, strings->get("type_2"));
	type2_button->setCoordinates(0.0f, 450.0f);
	type2_button->setDimensions(130.0f, 40.0f);
	type2_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected_type.setPosition(110.0f, 450.0f);
		map->setType(2);
		textures.loadMapType(2);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type2_button);

	std::shared_ptr<Button> type3_button = std::make_shared<Button>(window, strings->get("type_3"));
	type3_button->setCoordinates(0.0f, 495.0f);
	type3_button->setDimensions(130.0f, 40.0f);
	type3_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected_type.setPosition(110.0f, 495.0f);
		map->setType(3);
		textures.loadMapType(3);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type3_button);

	std::shared_ptr<Button> type4_button = std::make_shared<Button>(window, strings->get("type_4"));
	type4_button->setCoordinates(0.0f, 540.0f);
	type4_button->setDimensions(130.0f, 40.0f);
	type4_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		selected_type.setPosition(110.0f, 540.0f);
		map->setType(4);
		textures.loadMapType(4);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type4_button);

	map = std::make_shared<Map>();

	background.setSize(sf::Vector2f(130.0, window->getSize().y));
	background.setFillColor(sf::Color(0, 0, 100, 255));

	start.setSize(sf::Vector2f(50.0f, 100.0f));
	start.setFillColor(sf::Color::Green);
	start.setPosition(map->getPlayerPosition());
	finish.setSize(sf::Vector2f(50.0f, 50.0f));
	finish.setFillColor(sf::Color::Red);
	finish.setPosition(map->getFinishPosition());

	selected_type.setSize(sf::Vector2f(20.0f, 40.0f));
	selected_type.setFillColor(sf::Color::Green);
	selected_type.setPosition(110.0f, 405.0f);

	textures.loadMapType(1);
	map->setGroundTexture(textures.getGround());
}

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	:EditorState(window)
{
	this->map = map;

	textures.loadMapType(map->getType());
	map->setGroundTexture(textures.getGround());

	sf::Vector2f player_coor = map->getPlayerPosition();
	start.setPosition(player_coor.x, player_coor.y);

	sf::Vector2f finish_coor = map->getFinishPosition();
	finish.setPosition(finish_coor.x, finish_coor.y);

	switch (map->getType())
	{
	case 1:
		selected_type.setPosition(110.0f, 405.0f);
		break;
	case 2:
		selected_type.setPosition(110.0f, 450.0f);
		break;
	case 3:
		selected_type.setPosition(110.0f, 495.0f);
		break;
	case 4:
		selected_type.setPosition(110.0f, 540.0f);
		break;
	defaut:
		std::cout << "ERROR! Undefined type of the map!\n";
	}
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
				map->addShape(points, textures.getGround());
				points.clear();
			}
		}
	}
}

void EditorState::handleMouseModeFire(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i coor = sf::Mouse::getPosition(*State::window);
			std::cout << "fire, coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
			if (coor.x > 130)
			{
				points.push_back(sf::Vector2f(coor.x - 1, coor.y - 1));
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			if (points.size() >= 3)
			{
				map->addShape(points, nullptr);
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

void EditorState::handleMouseModeEnemy(sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i coor = sf::Mouse::getPosition(*State::window);
			std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
			if (coor.x > 130)
			{
				std::shared_ptr<sf::RectangleShape> enemy_rect = std::make_shared<sf::RectangleShape>();
				enemy_rect->setPosition(coor.x, coor.y);
				enemy_rect->setFillColor(sf::Color(236, 183, 0, 255));
				enemy_rect->setSize(sf::Vector2f(50.0f, 100.0f));
				map->addEnemy(enemy_rect);
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
	case FIRE:
		handleMouseModeFire(event);
		break;
	case PLAYER:
		handleMouseModePlayer(event);
		break;
	case FINISH:
		handleMouseModeFinish(event);
		break;
	case ENEMY:
		handleMouseModeEnemy(event);
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
	window->draw(selected_type);

	window->display();
}