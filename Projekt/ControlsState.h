#ifndef CONTROLS_STATE_H
#define CONTROLS_STATE_H
#include <memory>
#include <list>
#include <tuple>
#include "State.h"
#include "Control.h"
#include "KeyField.h"

class ControlsState : public State
{
private:
	sf::Font font;
	sf::Text title;
	sf::RectangleShape background;

	std::list<std::shared_ptr<Control>> controls;

	std::shared_ptr<KeyField> left_field;
	std::shared_ptr<KeyField> right_field;
	std::shared_ptr<KeyField> crouch_field;
	std::shared_ptr<KeyField> jump_field;

	void save();
	std::tuple<sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key>
		load();
public:
	ControlsState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~ControlsState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif
