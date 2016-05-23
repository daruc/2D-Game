#ifndef CONTROLS_STATE_H
#define CONTROLS_STATE_H
#include <memory>
#include "State.h"

class ControlsState : public State
{
public:
	ControlsState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~ControlsState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif
