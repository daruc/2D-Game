#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class State;
class App
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<State> currentState;
public:
	App();
	~App();
	void init();
	void run();

	inline std::shared_ptr<sf::RenderWindow> getWindow() { return window; }
};

#endif
