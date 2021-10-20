#ifndef COMMAND_ADD_ENEMY_H
#define COMMAND_ADD_ENEMY_H

#include <SFML/Graphics.hpp>
#include "EditorCommand.h"


class EditorMap;

class CommandAddEnemy : public EditorCommand
{
private:
	EditorMap* editor_map;
	sf::Vector2f position;

public:
	CommandAddEnemy(EditorMap* editor_map, sf::Vector2f position);
	void execute() override;
	void undo() override;
};

#endif