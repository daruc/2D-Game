#include <memory>
#include <iostream>
#include <thread>
#include <sstream>

#include "EditorState.h"
#include "../GUI/Button.h"
#include "../GUI/SelectableButton.h"
#include "../MainManuState.h"
#include "../SaveMapState.h"
#include "../LoadMapState.h"
#include "../Strings.h"
#include "GroundEditorMouseMode.h"
#include "PlayerEditorMouseMode.h"
#include "FinishEditorMouseMode.h"
#include "EnemyEditorMouseMode.h"
#include "FireEditorMouseMode.h"
#include "EditorCommand.h"


const sf::Vector2f BUTTON_DIMENSIONS(130.0f, 40.0f);

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window)
	: State(window), editor_map(window)
{
	initDefaultMouseMode();
	Strings* strings = Strings::Instance();
	createButtons(strings);
	type1_button->select();
}

void EditorState::initDefaultMouseMode()
{
	mouse_mode = std::make_shared<GroundEditorMouseMode>(window, this);
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
	save_button->setPosition(sf::Vector2f(0.0f, 90.0f));
	save_button->setDimensions(BUTTON_DIMENSIONS);
	save_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		std::shared_ptr<Map> map = editor_map.getMap();
		State::nextState = std::make_shared<SaveMapState>(State::window, map);
	});
	controls.push_back(save_button);
}

void EditorState::createLoadButton(Strings* strings)
{
	std::shared_ptr<Button> load_button = std::make_shared<Button>(window, strings->get("load"));
	load_button->setPosition(sf::Vector2f(0.0f, 135.f));
	load_button->setDimensions(BUTTON_DIMENSIONS);
	load_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		std::shared_ptr<Map> map = editor_map.getMap();
		State::nextState = std::make_shared<LoadMapState>(State::window, map);
	});
	controls.push_back(load_button);
}

void EditorState::createPlayerButton(Strings* strings)
{
	std::shared_ptr<Button> begin_button = std::make_shared<Button>(window, strings->get("player"));
	begin_button->setPosition(sf::Vector2f(0.0f, 180.0f));
	begin_button->setDimensions(BUTTON_DIMENSIONS);
	begin_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<PlayerEditorMouseMode>(window, this);
	});
	controls.push_back(begin_button);
}

void EditorState::createFinishButton(Strings* strings)
{
	std::shared_ptr<Button> finish_button = std::make_shared<Button>(window, strings->get("finish"));
	finish_button->setPosition(sf::Vector2f(0.0f, 225.0f));
	finish_button->setDimensions(BUTTON_DIMENSIONS);
	finish_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<FinishEditorMouseMode>(window, this);
	});
	controls.push_back(finish_button);
}

void EditorState::createGroundButton(Strings* strings)
{
	std::shared_ptr<Button> ground_button = std::make_shared<Button>(window, strings->get("ground"));
	ground_button->setPosition(sf::Vector2f(0.0f, 270.0f));
	ground_button->setDimensions(BUTTON_DIMENSIONS);
	ground_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<GroundEditorMouseMode>(window, this);
		editor_map.clearPoints();
	});
	controls.push_back(ground_button);
}

void EditorState::createFireButton(Strings* strings)
{
	std::shared_ptr<Button> fire_button = std::make_shared<Button>(window, strings->get("fire"));
	fire_button->setPosition(sf::Vector2f(0.0f, 315.0f));
	fire_button->setDimensions(BUTTON_DIMENSIONS);
	fire_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<FireEditorMouseMode>(window, this);
		editor_map.clearPoints();
	});
	controls.push_back(fire_button);
}

void EditorState::createEnemyButton(Strings* strings)
{
	std::shared_ptr<Button> enemy_button = std::make_shared<Button>(window, strings->get("enemy"));
	enemy_button->setPosition(sf::Vector2f(0.0f, 360.0f));
	enemy_button->setDimensions(BUTTON_DIMENSIONS);
	enemy_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		mouse_mode = std::make_shared<EnemyEditorMouseMode>(window, this);
	});
	controls.push_back(enemy_button);
}

void EditorState::createType1Button(Strings* strings)
{
	type1_button = std::make_shared<SelectableButton>(window, strings->get("type_1"));
	type1_button->setPosition(sf::Vector2f(0.0f, 405.0f));
	type1_button->setDimensions(BUTTON_DIMENSIONS);
	type1_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		editor_map.setMapType1();
	});
	controls.push_back(type1_button);
	groundTypesButtonGroup.addSelectableButton(type1_button);
}

void EditorState::createType2Button(Strings* strings)
{
	type2_button = std::make_shared<SelectableButton>(window, strings->get("type_2"));
	type2_button->setPosition(sf::Vector2f(0.0f, 450.0f));
	type2_button->setDimensions(BUTTON_DIMENSIONS);
	type2_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		editor_map.setMapType2();
	});
	controls.push_back(type2_button);
	groundTypesButtonGroup.addSelectableButton(type2_button);
}

void EditorState::createType3Button(Strings* strings)
{
	type3_button = std::make_shared<SelectableButton>(window, strings->get("type_3"));
	type3_button->setPosition(sf::Vector2f(0.0f, 495.0f));
	type3_button->setDimensions(BUTTON_DIMENSIONS);
	type3_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		editor_map.setMapType3();
	});
	controls.push_back(type3_button);
	groundTypesButtonGroup.addSelectableButton(type3_button);
}

void EditorState::createType4Button(Strings* strings)
{
	type4_button = std::make_shared<SelectableButton>(window, strings->get("type_4"));
	type4_button->setPosition(sf::Vector2f(0.0f, 540.0f));
	type4_button->setDimensions(BUTTON_DIMENSIONS);
	type4_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		editor_map.setMapType4();
	});
	controls.push_back(type4_button);
	groundTypesButtonGroup.addSelectableButton(type4_button);
}

void EditorState::createBackButton(Strings* strings)
{
	std::shared_ptr<Button> back_button = std::make_shared<Button>(window, strings->get("undo"));
	back_button->setPosition(sf::Vector2f(0.0f, 45.0f));
	back_button->setDimensions(BUTTON_DIMENSIONS);
	back_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;

		if (!executed_commands.empty())
		{
			executed_commands.top()->undo();
			executed_commands.pop();
		}
	});
	controls.push_back(back_button);
}

void EditorState::createMenuButton(Strings* strings)
{
	std::shared_ptr<Button> menu_button = std::make_shared<Button>(window, strings->get("menu"));
	menu_button->setPosition(sf::Vector2f(0.0f, 0.0f));
	menu_button->setDimensions(BUTTON_DIMENSIONS);
	menu_button->addListener([this](std::string str)->void {
		std::cout << "click " << str << std::endl;
		State::nextState = std::make_shared<MainMenuState>(State::window);
	});
	controls.push_back(menu_button);
}

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window), editor_map(window, map)
{
	initDefaultMouseMode();
	Strings* strings = Strings::Instance();
	createButtons(strings);
	selectMapTypeButton(map);
}

void EditorState::selectMapTypeButton(std::shared_ptr<Map> map)
{
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
	}
}

EditorState::~EditorState()
{

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
		{
			window->close();
			break;
		}
		
		handleControlsEvent(event);
		handleMouse(event);
		editor_map.handleEvent(event);
	}
}

void EditorState::handleControlsEvent(sf::Event & event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void EditorState::update(float delta_seconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(delta_seconds);
	}
}

void EditorState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	State::window->clear();

	editor_map.draw(window);

	//GUI
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}

	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void EditorState::addPoint(sf::Vector2f point)
{
	editor_map.addPoint(point);
}

size_t EditorState::getPointsCount() const
{
	return editor_map.getPointsCount();
}

void EditorState::addGroundShape()
{
	editor_map.addGroundShape();
}

void EditorState::addFireShape()
{
	editor_map.addFireShape();
}

std::list<sf::Vector2f> EditorState::getPoints() const
{
	return editor_map.getPoints();
}

void EditorState::clearPoints()
{
	editor_map.clearPoints();
}

sf::Vector2f EditorState::getPlayerPosition() const
{
	return editor_map.getPlayerPosition();
}

void EditorState::setPlayerPosition(sf::Vector2f newPosition)
{
	editor_map.setPlayerPosition(newPosition);
}

sf::Vector2f EditorState::getFinishPosition() const
{
	return editor_map.getFinishPosition();
}

void EditorState::setFinishPosition(sf::Vector2f newPosition)
{
	editor_map.setFinishPosition(newPosition);
}

void EditorState::addEnemy(sf::Vector2f position)
{
	editor_map.addEnemy(position);
}

void EditorState::executeCommand(std::shared_ptr<EditorCommand> editor_command)
{
	editor_command->execute();
	executed_commands.push(editor_command);
}

EditorMap* EditorState::getEditorMapPtr()
{
	return &editor_map;
}