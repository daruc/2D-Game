#ifndef PLAYER_EDITOR_MOUSE_MODE_H
#define PLAYER_EDITOR_MOUSE_MODE_H

#include "EditorMouseMode.h"


class PlayerEditorMouseMode : public EditorMouseMode
{
public:
	PlayerEditorMouseMode(std::shared_ptr<sf::RenderWindow> window, EditorState* editor_state);
	void handleMouse(sf::Event& event) override;
};

#endif // !PLAYER_EDITOR_MOUSE_MODE_H
