#include <iostream>

#include <SFML/Graphics.hpp>

#include "EnemyEditorMouseMode.h"
#include "EditorState.h"
#include "CommandAddEnemy.h"


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
			sf::Vector2f position(coor);
			auto command = std::make_shared<CommandAddEnemy>(editor_state->getEditorMapPtr(), position);
			editor_state->executeCommand(command);
		}
	}
}