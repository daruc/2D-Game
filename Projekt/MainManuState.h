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
	std::vector<std::shared_ptr<Control>> controls;

public:
	MainMenuState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~MainMenuState();
	virtual void handleEvents();
	void update() override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};


#endif
