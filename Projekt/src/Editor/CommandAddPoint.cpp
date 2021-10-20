#include "CommandAddPoint.h"
#include "EditorMap.h"


CommandAddPoint::CommandAddPoint(EditorMap* editor_map, sf::Vector2f point)
	: editor_map(editor_map), point(point)
{

}

void CommandAddPoint::execute()
{
	editor_map->addPoint(point);
}

void CommandAddPoint::undo()
{
	editor_map->popPoint();
}