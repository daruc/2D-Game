#ifndef MAP_MENU_STATE_H
#define MAP_MENU_STATE_H
#include <memory>
#include <list>
#include "State.h"
#include "Control.h"

class MapMenuState : public State
{
private:
	std::list<std::shared_ptr<Control>> controls;
public:
	MapMenuState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~MapMenuState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif