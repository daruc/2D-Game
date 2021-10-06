#include "FireEditorMouseMode.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include "EditorState.h"


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
		editor_state->addPoint(sf::Vector2f(coor.x - 1, coor.y - 1));
		editor_state->pushUndoAction("remove_point");
	}
}

void FireEditorMouseMode::handleRightMouseButton()
{
	if (editor_state->getPointsCount() >= 3)
	{
		editor_state->addFireShape();

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
