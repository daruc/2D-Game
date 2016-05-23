#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <memory>

class State
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<State> nextState;
public:
	State(std::shared_ptr<sf::RenderWindow> window);
	virtual ~State();
	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	inline std::shared_ptr<State> getNextState() { return nextState; }
};

#endif