#ifndef ENEMY_EDITOR_MOUSE_MODE_H
#define ENEMY_EDITOR_MOUSE_MODE_H

#include "EditorMouseMode.h"

class EnemyEditorMouseMode : public EditorMouseMode
{
public:
	EnemyEditorMouseMode(std::shared_ptr<sf::RenderWindow> window, EditorState* editor_state);
	void handleMouse(sf::Event & event) override;
};

#endif // !ENEMY_EDITOR_MOUSE_MODE_H
