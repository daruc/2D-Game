#ifndef LOAD_MAP_STATE
#define LOAD_MAP_STATE
#include <list>
#include "State.h"
#include "Control.h"
#include "Map.h"

class LoadMapState : public State
{
private:
	sf::RectangleShape background;
	std::shared_ptr<Map> prev_map;
	std::vector<std::shared_ptr<Control>> controls;
	sf::Font font;
	sf::Text title;
public:
	LoadMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~LoadMapState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif