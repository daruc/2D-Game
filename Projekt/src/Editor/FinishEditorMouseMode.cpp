#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "FinishEditorMouseMode.h"
#include "EditorState.h"


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
		if (coor.x > 130)
		{
			sf::Vector2f finish_position = editor_state->getFinishPosition();
			std::stringstream stream;
			stream << "move_finish|" << finish_position.x << "|" << finish_position.y;
			editor_state->pushUndoAction(stream.str());
			editor_state->setFinishPosition(sf::Vector2f(coor));
		}
	}
}