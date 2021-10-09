#ifndef FINISH_EDITOR_MOUSE_MODE_H
#define FINISH_EDITOR_MOUSE_MODE_H

#include "EditorMouseMode.h"


class FinishEditorMouseMode : public EditorMouseMode
{
public:
	FinishEditorMouseMode(std::shared_ptr<sf::RenderWindow> window, EditorState* editor_state);
	void handleMouse(sf::Event & event) override;
};

#endif // !FINISH_EDITOR_MOUSE_MODE_H
