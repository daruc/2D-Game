#ifndef FIRE_EDITOR_MOUSE_MODE_H
#define FIRE_EDITOR_MOUSE_MODE_H

#include "EditorMouseMode.h"

class FireEditorMouseMode : public EditorMouseMode
{
private:
	void handleRightMouseButton();
	void handleLeftMouseButton();

public:
	FireEditorMouseMode(std::shared_ptr<sf::RenderWindow> window, EditorState* editor_state);
	void handleMouse(sf::Event& event) override;
};

#endif
