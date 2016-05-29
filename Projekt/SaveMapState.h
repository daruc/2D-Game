#ifndef SAVE_MAP_STATE
#define SAVE_MAP_STATE
#include <list>
#include <SFML/Graphics.hpp>
#include "Control.h"
#include "State.h"

class SaveMapState : public State
{
private:
	std::list<std::shared_ptr<Control>> controls;
	std::shared_ptr<Map> map;
	void save(sf::String filename);
public:
	SaveMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~SaveMapState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif
