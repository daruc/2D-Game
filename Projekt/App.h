#ifndef APP_H
#define APP_H

#include <memory>


namespace sf
{
	class RenderWindow;
}

class State;

class App
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<State> currentState;

public:
	void init();
	void run();
};

#endif
