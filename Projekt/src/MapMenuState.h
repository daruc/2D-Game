#ifndef MAP_MENU_STATE_H
#define MAP_MENU_STATE_H

#include <memory>
#include <list>

#include "GUI/Control.h"
#include "State.h"
#include "Textures.h"


class MapMenuState : public State
{
private:
	sf::Font font;
	sf::Text title;
	std::vector<std::shared_ptr<Control>> controls;
	sf::RectangleShape background;
	sf::Sprite tick[18];
	bool completed[18];
	Textures textures;

public:
	MapMenuState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~MapMenuState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif