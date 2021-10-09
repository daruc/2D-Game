#ifndef GROUND_EDITOR_MOUSE_MODE_H
#define GROUND_EDITOR_MOUSE_MODE_H

#include "EditorMouseMode.h"


class GroundEditorMouseMode : public EditorMouseMode
{
private:
	void handleRightMouseButton();
	void handleLeftMouseButton();

public:
	GroundEditorMouseMode(std::shared_ptr<sf::RenderWindow> window, EditorState* editor_state);
	void handleMouse(sf::Event& event) override;
};

#endif
