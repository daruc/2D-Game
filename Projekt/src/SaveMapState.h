#ifndef SAVE_MAP_STATE
#define SAVE_MAP_STATE

#include <list>

#include <SFML/Graphics.hpp>

#include "GUI/Control.h"
#include "State.h"


class Map;


class SaveMapState : public State
{
private:
	sf::RectangleShape background;
	std::vector<std::shared_ptr<Control>> controls;
	std::shared_ptr<Map> map;
	sf::Font font;
	sf::Text title;

	void save(sf::String filename);

public:
	SaveMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~SaveMapState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> renderWindow) override;
};

#endif