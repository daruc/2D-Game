#include "CommandMoveFinish.h"
#include "EditorMap.h"


CommandMoveFinish::CommandMoveFinish(EditorMap* editor_map, sf::Vector2f position)
	: editor_map(editor_map),
	position(position),
	old_position(editor_map->getFinishPosition(Space::MAP))
{

}

void CommandMoveFinish::execute()
{
	editor_map->setFinishPosition(position, Space::SCREEN);
}

void CommandMoveFinish::undo()
{
	editor_map->setFinishPosition(old_position, Space::MAP);
}