#ifndef LOAD_MAP_STATE
#define LOAD_MAP_STATE
#include <list>
#include "State.h"
#include "Control.h"

class LoadMapState : public State
{
private:
	std::list<std::shared_ptr<Control>> controls;
public:
	LoadMapState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~LoadMapState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif