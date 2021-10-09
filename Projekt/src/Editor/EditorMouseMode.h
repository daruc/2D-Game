#ifndef EDITOR_MOUSE_MODE_H
#define EDITOR_MOUSE_MODE_H

#include <memory>


namespace sf
{
	class Event;
	class RenderWindow;
}

class EditorState;

class EditorMouseMode
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	EditorState* editor_state;

	bool isLeftMouseButtonPressed(const sf::Event& event) const;
	bool isRightMouseButtonPressed(const sf::Event& event) const;

public:
	EditorMouseMode(std::shared_ptr<sf::RenderWindow> window, EditorState* editor_state);
	virtual ~EditorMouseMode() = default;
	virtual void handleMouse(sf::Event& event) = 0;
};

#endif
