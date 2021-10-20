#include <iostream>
#include <sstream>

#include <SFML/Window.hpp>

#include "PlayerEditorMouseMode.h"
#include "EditorState.h"
#include "CommandMovePlayer.h"


PlayerEditorMouseMode::PlayerEditorMouseMode(std::shared_ptr<sf::RenderWindow> window,
	EditorState* editor_state) : EditorMouseMode(window, editor_state)
{

}

void PlayerEditorMouseMode::handleMouse(sf::Event & event)
{
	if (isLeftMouseButtonPressed(event))
	{
		sf::Vector2i coor = sf::Mouse::getPosition(*window);
		std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
		if (coor.x > 130)
		{
			sf::Vector2f position(coor);
			auto command = std::make_shared<CommandMovePlayer>(editor_state->getEditorMapPtr(), position);
			editor_state->executeCommand(command);
		}
	}
}