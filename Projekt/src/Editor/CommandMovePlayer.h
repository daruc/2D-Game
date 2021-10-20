#ifndef COMMAND_MOVE_PLAYER_H
#define COMMAND_MOVE_PLAYER_H

#include <SFML/Graphics.hpp>
#include "EditorCommand.h"


class EditorMap;

class CommandMovePlayer : public EditorCommand
{
private:
	EditorMap* editor_map;
	sf::Vector2f position;
	sf::Vector2f old_position;

public:
	CommandMovePlayer(EditorMap* editor_map, sf::Vector2f position);
	void execute() override;
	void undo() override;
};

#endif