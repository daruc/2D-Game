#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "FinishEditorMouseMode.h"
#include "EditorState.h"
#include "CommandMoveFinish.h"
#include "EditorConstants.h"


FinishEditorMouseMode::FinishEditorMouseMode(std::shared_ptr<sf::RenderWindow> window,
	EditorState* editor_state)	: EditorMouseMode(window, editor_state)
{

}

void FinishEditorMouseMode::handleMouse(sf::Event & event)
{
	if (isLeftMouseButtonPressed(event))
	{
		sf::Vector2i coor = sf::Mouse::getPosition(*window);
		std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
		if (coor.x > EditorConstants::LEFT_MAP_EDGE)
		{
			sf::Vector2f new_position(coor);
			auto command = std::make_shared<CommandMoveFinish>(editor_state->getEditorMapPtr(), new_position);
			editor_state->executeCommand(command);
		}
	}
}