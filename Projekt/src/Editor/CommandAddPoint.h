#ifndef COMMAND_ADD_POINT
#define COMMAND_ADD_POINT

#include <SFML/Graphics.hpp>
#include "EditorCommand.h"


class EditorMap;

class CommandAddPoint : public EditorCommand
{
private:
	EditorMap* editor_map;
	sf::Vector2f point;

public:
	CommandAddPoint(EditorMap* editor_map, sf::Vector2f point);
	void execute() override;
	void undo() override;
};

#endif // !COMMAND_ADD_POINT
