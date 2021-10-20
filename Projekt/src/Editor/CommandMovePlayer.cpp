#include "CommandMovePlayer.h"
#include "EditorMap.h"


CommandMovePlayer::CommandMovePlayer(EditorMap* editor_map, sf::Vector2f position)
	: editor_map(editor_map),
	position(position),
	old_position(editor_map->getPlayerPosition(Space::MAP))
{

}

void CommandMovePlayer::execute()
{
	editor_map->setPlayerPosition(position, Space::SCREEN);
}

void CommandMovePlayer::undo()
{
	editor_map->setPlayerPosition(old_position, Space::MAP);
}