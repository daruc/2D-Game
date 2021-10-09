#ifndef STATE_H
#define STATE_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "Updatable.h"


class State : public Updatable, public Drawable
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<State> nextState;

public:
	State(std::shared_ptr<sf::RenderWindow> window);
	virtual ~State();
	virtual void handleEvents() = 0;
	inline std::shared_ptr<State> getNextState() { return nextState; }
};

#endif