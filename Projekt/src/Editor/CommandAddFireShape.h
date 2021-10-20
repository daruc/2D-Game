#ifndef COMMAND_ADD_FIRE_SHAPE_H
#define COMMAND_ADD_FIRE_SHAPE_H

#include <stack>
#include <SFML/Graphics.hpp>
#include "EditorCommand.h"


class EditorMap;

class CommandAddFireShape : public EditorCommand
{
private:
	EditorMap* editor_map;
	std::stack<sf::Vector2f> removed_points;
	
public:
	CommandAddFireShape(EditorMap* editor_map);
	void execute() override;
	void undo() override;
};

#endif