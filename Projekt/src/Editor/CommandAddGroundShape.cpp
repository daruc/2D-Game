#include "CommandAddGroundShape.h"
#include "EditorMap.h"

CommandAddGroundShape::CommandAddGroundShape(EditorMap* editor_map)
	: editor_map(editor_map)
{

}

void CommandAddGroundShape::execute()
{
	editor_map->addGroundShape();

	while (editor_map->getPointsCount() > 0)
	{
		sf::Vector2f point = editor_map->popPoint(Space::MAP);
		removed_points.push(point);
	}
}

void CommandAddGroundShape::undo()
{
	editor_map->removeLast();
	while (!removed_points.empty())
	{
		sf::Vector2f point = removed_points.top();
		removed_points.pop();
		editor_map->addPoint(point, Space::MAP);
	}
}