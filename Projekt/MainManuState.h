#ifndef MAIN_MENU_STATE
#define MAIN_MENU_STATE
#include <list>
#include <memory>
#include "State.h"
#include "Control.h"
#include "App.h"

class MainMenuState : public State
{
private:
	std::list<std::shared_ptr<Control>> controls;
public:
	MainMenuState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~MainMenuState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};


#endif
