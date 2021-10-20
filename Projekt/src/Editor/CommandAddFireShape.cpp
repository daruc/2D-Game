#include "CommandAddFireShape.h"
#include "EditorMap.h"


CommandAddFireShape::CommandAddFireShape(EditorMap* editor_map)
	: editor_map(editor_map)
{

}

void CommandAddFireShape::execute()
{
	editor_map->addFireShape();

	while (editor_map->getPointsCount() > 0)
	{
		sf::Vector2f removed_point = editor_map->popPoint();
		removed_points.push(removed_point);
	}
}

void CommandAddFireShape::undo()
{
	editor_map->removeLast();

	while (!removed_points.empty())
	{
		sf::Vector2f removed_point = removed_points.top();
		removed_points.pop();
		editor_map->addPoint(removed_point);
	}
}