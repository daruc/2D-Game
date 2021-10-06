#include <memory>
#include <iostream>
#include <thread>
#include <sstream>
#include "EditorState.h"
#include "Button.h"
#include "MainManuState.h"
#include "SaveMapState.h"
#include "LoadMapState.h"
#include "Strings.h"
#include "GroundEditorMouseMode.h"
#include "PlayerEditorMouseMode.h"
#include "FinishEditorMouseMode.h"
#include "EnemyEditorMouseMode.h"
#include "FireEditorMouseMode.h"
#include "SelectableButton.h"


EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window)
	: State(window), view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y))
{
	Strings* strings = Strings::Instance();
	mouse_mode = std::make_shared<GroundEditorMouseMode>(window, this);

	createButtons(strings);

	map = std::make_shared<Map>();

	background.setSize(sf::Vector2f(130.0, window->getSize().y));
	background.setFillColor(sf::Color(0, 0, 100, 255));

	initStart();
	initFinish();

	textures.loadMapType(1);
	map->setGroundTexture(textures.getGround());
	type1_button->select();
}

void EditorState::createButtons(Strings* strings)
{
	createMenuButton(strings);
	createBackButton(strings);
	createSaveButton(strings);
	createLoadButton(strings);
	createPlayerButton(strings);
	createFinishButton(strings);
	createGroundButton(strings);
	createFireButton(strings);
	createEnemyButton(strings);
	createType1Button(strings);
	createType2Button(strings);
	createType3Button(strings);
	createType4Button(strings);
}

void EditorState::createSaveButton(Strings* strings)
{
	std::shared_ptr<Button> save_button = std::make_shared<Button>(window, strings->get("save"));
	save_button->setCoordinates(0.0f, 90.0f);
	save_button->setDimensions(130.0f, 40.0f);
	save_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<SaveMapState>(State::window, map);
	});
	controls.push_back(save_button);
}

void EditorState::createLoadButton(Strings* strings)
{
	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->get("load"));
	load_button->setCoordinates(0.0f, 135.f);
	load_button->setDimensions(130.0f, 40.0f);
	load_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<LoadMapState>(State::window, map);
	});
	controls.push_back(load_button);
}

void EditorState::createPlayerButton(Strings* strings)
{
	std::shared_ptr<Button> begin_button = std::make_shared<Button>(window, strings->get("player"));
	begin_button->setCoordinates(0.0f, 180.0f);
	begin_button->setDimensions(130.0f, 40.0f);
	begin_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<PlayerEditorMouseMode>(window, this);
	});
	controls.push_back(begin_button);
}

void EditorState::createFinishButton(Strings* strings)
{
	std::shared_ptr<Button> finish_button = std::make_shared<Button>(window, strings->get("finish"));
	finish_button->setCoordinates(0.0f, 225.0f);
	finish_button->setDimensions(130.0f, 40.0f);
	finish_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<FinishEditorMouseMode>(window, this);
	});
	controls.push_back(finish_button);
}

void EditorState::createGroundButton(Strings* strings)
{
	std::shared_ptr<Button> ground_button = std::make_shared<Button>(window, strings->get("ground"));
	ground_button->setCoordinates(0.0f, 270.0f);
	ground_button->setDimensions(130.0f, 40.0f);
	ground_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<GroundEditorMouseMode>(window, this);
		points.clear();
	});
	controls.push_back(ground_button);
}

void EditorState::createFireButton(Strings* strings)
{
	std::shared_ptr<Button> fire_button = std::make_shared<Button>(window, strings->get("fire"));
	fire_button->setCoordinates(0.0f, 315.0f);
	fire_button->setDimensions(130.0f, 40.0f);
	fire_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<FireEditorMouseMode>(window, this);
		points.clear();
	});
	controls.push_back(fire_button);
}

void EditorState::createEnemyButton(Strings* strings)
{
	std::shared_ptr<Button> enemy_button = std::make_shared<Button>(window, strings->get("enemy"));
	enemy_button->setCoordinates(0.0f, 360.0f);
	enemy_button->setDimensions(130.0f, 40.0);
	enemy_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<EnemyEditorMouseMode>(window, this);
	});
	controls.push_back(enemy_button);
}

void EditorState::createType1Button(Strings* strings)
{
	type1_button = std::make_shared<SelectableButton>(window, strings->get("type_1"));
	type1_button->setCoordinates(0.0f, 405.0f);
	type1_button->setDimensions(130.0f, 40.0f);
	type1_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		map->setType(1);
		textures.loadMapType(1);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type1_button);
	groundTypesButtonGroup.addSelectableButton(type1_button);
}

void EditorState::createType2Button(Strings* strings)
{
	type2_button = std::make_shared<SelectableButton>(window, strings->get("type_2"));
	type2_button->setCoordinates(0.0f, 450.0f);
	type2_button->setDimensions(130.0f, 40.0f);
	type2_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		map->setType(2);
		textures.loadMapType(2);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type2_button);
	groundTypesButtonGroup.addSelectableButton(type2_button);
}

void EditorState::createType3Button(Strings* strings)
{
	type3_button = std::make_shared<SelectableButton>(window, strings->get("type_3"));
	type3_button->setCoordinates(0.0f, 495.0f);
	type3_button->setDimensions(130.0f, 40.0f);
	type3_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		map->setType(3);
		textures.loadMapType(3);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type3_button);
	groundTypesButtonGroup.addSelectableButton(type3_button);
}

void EditorState::createType4Button(Strings* strings)
{
	type4_button = std::make_shared<SelectableButton>(window, strings->get("type_4"));
	type4_button->setCoordinates(0.0f, 540.0f);
	type4_button->setDimensions(130.0f, 40.0f);
	type4_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		map->setType(4);
		textures.loadMapType(4);
		map->setGroundTexture(textures.getGround());
	});
	controls.push_back(type4_button);
	groundTypesButtonGroup.addSelectableButton(type4_button);
}

void EditorState::createBackButton(Strings* strings)
{
	std::shared_ptr<Button> back_button = std::make_shared<Button>(window, strings->get("undo"));
	back_button->setCoordinates(0.0f, 45.0f);
	back_button->setDimensions(130.0f, 40.0f);
	back_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;

		if (!undo_stack.empty())
		{
			std::string str = undo_stack.top();
			std::cout << "undo_stack: " << str << std::endl;
			undo_stack.pop();

			if (str == "remove_point")
			{
				points.pop_back();
			}
			else if (str.substr(0, 12) == "remove_shape")
			{
				parseAndExecuteRemoveShape(str);
			}
			else if (str.substr(0, 11) == "move_player")
			{
				str = str.substr(12);
				std::size_t position = str.find("|");
				std::string coor_x = str.substr(0, position);
				std::string coor_y = str.substr(position + 1);
				std::stringstream stream;
				sf::Vector2f vector;
				stream << coor_x;
				stream >> vector.x;
				stream.clear();
				stream << coor_y;
				stream >> vector.y;

				map->setPlayerPosition(vector.x, vector.y, false);
				start.setPosition(vector.x, vector.y);
			}
			else if (str.substr(0, 11) == "move_finish")
			{
				str = str.substr(12);
				std::size_t position = str.find("|");
				std::string coor_x = str.substr(0, position);
				std::string coor_y = str.substr(position + 1);
				std::stringstream stream;
				sf::Vector2f vector;
				stream << coor_x;
				stream >> vector.x;
				stream.clear();
				stream << coor_y;
				stream >> vector.y;

				map->setFinishPosition(vector.x, vector.y, false);
				finish.setPosition(vector.x, vector.y);
			}
			else if (str == "remove_enemy")
			{
				map->getEnenemiesList()->pop_back();
			}
		}
	});
	controls.push_back(back_button);
}

void EditorState::createMenuButton(Strings* strings)
{
	std::shared_ptr<Button> menu_button = std::make_shared<Button>(window, strings->get("menu"));
	menu_button->setCoordinates(0.0f, 0.0f);
	menu_button->setDimensions(130.0f, 40.0f);
	menu_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(menu_button);
}

void EditorState::initStart()
{
	start.setSize(sf::Vector2f(50.0f, 100.0f));
	start.setFillColor(sf::Color::Green);
	start.setPosition(map->getPlayerPosition());
}

void EditorState::initFinish()
{
	finish.setSize(sf::Vector2f(50.0f, 50.0f));
	finish.setFillColor(sf::Color::Red);
	finish.setPosition(map->getFinishPosition());
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
		type1_button->select();
		break;
	case 2:
		type2_button->select();
		break;
	case 3:
		type3_button->select();
		break;
	case 4:
		type4_button->select();
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

void EditorState::handleMouse(sf::Event & event)
{
	mouse_mode->handleMouse(event);
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

void EditorState::update(float deltaSeconds)
{
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->update(deltaSeconds);
	}
}

void EditorState::draw(std::shared_ptr<sf::RenderWindow> window)
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
	map->draw(window);
	window->draw(start);

	// enemies
	for (auto enemy : enemies)
	{
		window->draw(*enemy);
	}

	window->draw(finish);
	window->setView(window->getDefaultView());

	window->draw(background);

	//GUI
	auto begin = controls.begin();
	auto end = controls.end();
	for (auto it = begin; it != end; ++it)
	{
		(*it)->draw(window);
	}

	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void EditorState::parseAndExecuteRemoveShape(std::string command)
{
	map->removeLast();
	std::string tail = command.substr(12);
	std::cout << "tail=" << tail << std::endl;
	while (!tail.empty())
	{
		tail = tail.substr(11);
		std::size_t position = tail.find("#");
		std::string str_coor = tail.substr(0, position);
		
		if (position == 4294967295)
			tail = "";
		else
			tail = tail.substr(position);

		position = str_coor.find("|");
		std::string str_x = str_coor.substr(0, position);
		std::string str_y = str_coor.substr(position + 1);

		std::stringstream stream;
		sf::Vector2f point;
		stream << str_x;
		stream >> point.x;
		stream.clear();
		stream << str_y;
		stream >> point.y;
		points.push_back(point);
	}
}

void EditorState::addPoint(sf::Vector2f point)
{
	points.push_back(point);
}

void EditorState::pushUndoAction(sf::String action)
{
	undo_stack.push(action);
}

size_t EditorState::getPointsCount() const
{
	return points.size();
}

void EditorState::addGroundShape()
{
	map->addShape(points, textures.getGround());
}

void EditorState::addFireShape()
{
	map->addShape(points, nullptr);
}

std::list<sf::Vector2f> EditorState::getPoints() const
{
	return points;
}

void EditorState::clearPoints()
{
	points.clear();
}

sf::Vector2f EditorState::getPlayerPosition() const
{
	return map->getPlayerPosition();
}

void EditorState::setPlayerPosition(sf::Vector2f newPosition)
{
	map->setPlayerPosition(newPosition.x, newPosition.y);
	sf::Vector2f new_coor = map->getPlayerPosition();
	start.setPosition(new_coor.x, new_coor.y);
}

sf::Vector2f EditorState::getFinishPosition() const
{
	return map->getFinishPosition();
}

void EditorState::setFinishPosition(sf::Vector2f newPosition)
{
	map->setFinishPosition(newPosition.x, newPosition.y);

	sf::Vector2f new_coor = map->getFinishPosition();
	finish.setPosition(new_coor.x, new_coor.y);
}

void EditorState::addEnemy(sf::Vector2f position)
{
	std::shared_ptr<sf::RectangleShape> enemy_rect = std::make_shared<sf::RectangleShape>();
	enemy_rect->setPosition(position.x, position.y);
	enemy_rect->setFillColor(sf::Color(236, 183, 0, 255));
	enemy_rect->setSize(sf::Vector2f(50.0f, 100.0f));
	map->addEnemy(enemy_rect);
	enemies.push_back(enemy_rect);
}