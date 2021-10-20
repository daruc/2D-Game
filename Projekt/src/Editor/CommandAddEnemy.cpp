#include "CommandAddEnemy.h"
#include "EditorMap.h"


CommandAddEnemy::CommandAddEnemy(EditorMap* editor_map, sf::Vector2f position)
	: editor_map(editor_map), position(position)
{

}

void CommandAddEnemy::execute()
{
	editor_map->addEnemy(position);
}

void CommandAddEnemy::undo()
{
	editor_map->popEnemy();
}