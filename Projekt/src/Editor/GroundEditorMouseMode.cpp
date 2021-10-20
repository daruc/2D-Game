#include <iostream>
#include <sstream>

#include <SFML/Window.hpp>

#include "../State.h"
#include "GroundEditorMouseMode.h"
#include "EditorState.h"
#include "CommandAddPoint.h"
#include "CommandAddGroundShape.h"


GroundEditorMouseMode::GroundEditorMouseMode(std::shared_ptr<sf::RenderWindow> window, 
	EditorState* editor_state) : EditorMouseMode(window, editor_state)
{

}

void GroundEditorMouseMode::handleMouse(sf::Event & event)
{
	if (isLeftMouseButtonPressed(event))
	{
		handleLeftMouseButton();
	}
	else if (isRightMouseButtonPressed(event))
	{
		handleRightMouseButton();
	}
}

void GroundEditorMouseMode::handleLeftMouseButton()
{
	sf::Vector2i coor = sf::Mouse::getPosition(*window);
	std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
	if (coor.x > 130)
	{
		sf::Vector2f position(coor.x - 1, coor.y - 1);
		auto command = std::make_shared<CommandAddPoint>(editor_state->getEditorMapPtr(), position);
		editor_state->executeCommand(command);
	}
}

void GroundEditorMouseMode::handleRightMouseButton()
{
	if (editor_state->getPointsCount() >= 3)
	{
		auto command = std::make_shared<CommandAddGroundShape>(editor_state->getEditorMapPtr());
		editor_state->executeCommand(command);
	}
}
