#ifndef APP_H
#define APP_H

#include <memory>
#include <string>


namespace sf
{
	class RenderWindow;
}

class State;

class App
{
private:
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const std::string TITLE = "Gra";

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<State> current_state;

	void changeCurrentState();

public:
	void init();
	void run();
};

#endif
