#include "EditorMouseMode.h"
#include <SFML/Window.hpp>

EditorMouseMode::EditorMouseMode(std::shared_ptr<sf::RenderWindow> window, EditorState * editor_state)
	: window(window), editor_state(editor_state)
{

}

bool EditorMouseMode::isLeftMouseButtonPressed(const sf::Event& event) const
{
	return (event.type == sf::Event::MouseButtonPressed) &&
		(event.mouseButton.button == sf::Mouse::Left);
}

bool EditorMouseMode::isRightMouseButtonPressed(const sf::Event& event) const
{
	return (event.type == sf::Event::MouseButtonPressed) &&
		(event.mouseButton.button == sf::Mouse::Right);
}