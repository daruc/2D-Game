#include "EnemyEditorMouseMode.h"
#include "EditorState.h"
#include <SFML/Graphics.hpp>
#include <iostream>


EnemyEditorMouseMode::EnemyEditorMouseMode(std::shared_ptr<sf::RenderWindow> window,
	EditorState* editor_state) : EditorMouseMode(window, editor_state)
{

}

void EnemyEditorMouseMode::handleMouse(sf::Event & event)
{
	if (isLeftMouseButtonPressed(event))
	{
		sf::Vector2i coor = sf::Mouse::getPosition(*window);
		std::cout << "coor.x = " << coor.x << ", coor.y = " << coor.y << std::endl;
		if (coor.x > 130)
		{
			editor_state->pushUndoAction("remove_enemy");
			editor_state->addEnemy(sf::Vector2f(coor));
		}
	}
}