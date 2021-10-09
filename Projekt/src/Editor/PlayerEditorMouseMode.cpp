#include <iostream>
#include <sstream>

#include <SFML/Window.hpp>

#include "PlayerEditorMouseMode.h"
#include "EditorState.h"


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
			sf::Vector2f player_position = editor_state->getPlayerPosition();
			std::stringstream stream;
			stream << "move_player|" << player_position.x << "|" << player_position.y;
			editor_state->pushUndoAction(stream.str());
			editor_state->setPlayerPosition(sf::Vector2f(coor));
		}
	}
}