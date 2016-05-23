#ifndef MAP_MENU_STATE_H
#define MAP_MENU_STATE_H
#include <memory>
#include "State.h"

class MapMenuState : public State
{
public:
	MapMenuState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~MapMenuState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif