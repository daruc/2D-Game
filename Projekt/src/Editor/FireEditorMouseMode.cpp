#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EditorState.h"
#include "FireEditorMouseMode.h"
#include "CommandAddFireShape.h"
#include "CommandAddPoint.h"


FireEditorMouseMode::FireEditorMouseMode(std::shared_ptr<sf::RenderWindow> window, 
	EditorState* editor_state)	: EditorMouseMode(window, editor_state)
{

}

void FireEditorMouseMode::handleMouse(sf::Event& event)
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

void FireEditorMouseMode::handleLeftMouseButton()
{
	sf::Vector2i coor = sf::Mouse::getPosition(*window);
	std::cout << "fire, coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
	if (coor.x > 130)
	{
		sf::Vector2f position(coor.x - 1, coor.y - 1);
		auto command = std::make_shared<CommandAddPoint>(editor_state->getEditorMapPtr(), position);
		editor_state->executeCommand(command);
	}
}

void FireEditorMouseMode::handleRightMouseButton()
{
	if (editor_state->getPointsCount() >= 3)
	{
		auto command = std::make_shared<CommandAddFireShape>(editor_state->getEditorMapPtr());
		editor_state->executeCommand(command);
	}
}
