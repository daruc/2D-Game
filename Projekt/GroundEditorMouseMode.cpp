#include "GroundEditorMouseMode.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include "State.h"
#include "EditorState.h"


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
		editor_state->addPoint(sf::Vector2f(coor.x - 1, coor.y - 1));
		editor_state->pushUndoAction("remove_point");
	}
}

void GroundEditorMouseMode::handleRightMouseButton()
{
	if (editor_state->getPointsCount() >= 3)
	{
		editor_state->addGroundShape();

		//Removing points
		std::stringstream strstream;
		strstream << "remove_shape";
		for (sf::Vector2f point : editor_state->getPoints())
		{
			strstream << "#add_point|" << point.x << "|" << point.y;
		}
		editor_state->clearPoints();
		editor_state->pushUndoAction(strstream.str());
	}
}
