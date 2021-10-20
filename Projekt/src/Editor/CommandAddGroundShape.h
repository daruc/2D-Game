#ifndef COMMAND_ADD_GROUND_SHAPE_H
#define COMMAND_ADD_GROUND_SHAPE_H

#include <SFML/Graphics.hpp>
#include <stack>
#include "EditorCommand.h"


class EditorMap;

class CommandAddGroundShape : public EditorCommand
{
private:
	EditorMap* editor_map;
	std::stack<sf::Vector2f> removed_points;

public:
	CommandAddGroundShape(EditorMap* editor_map);
	void execute() override;
	void undo() override;
};

#endif