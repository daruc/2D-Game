#ifndef MAP_MENU_STATE_H
#define MAP_MENU_STATE_H

#include <memory>
#include <list>
#include <vector>

#include "GUI/Control.h"
#include "State.h"
#include "Textures.h"
#include "GUI/GridLayout.h"


class Strings;
class TextField;

class MapMenuState : public State
{
private:
	sf::Font font;
	sf::Text title;

	GridLayout grid_layout;
	std::shared_ptr<TextField> text_field;
	std::vector<std::shared_ptr<Control>> controls;
	sf::RectangleShape background;
	Textures textures;

	sf::Vector2f calculateScreenCenter() const;
	sf::Vector2f calculateMapGridPosition() const;
	void createMapButtons(Strings* strings);
	void createMapButton(Strings* strings, size_t map_index, bool completed);
	std::string buildMapNameForIndex(size_t map_index);
	std::string buildMapFilePathForIndex(size_t map_index);
	void createBackButton(Strings* strings);
	void createMapTextField();
	void createLoadMapButton(Strings* strings);
	void initTitle(Strings* strings);
	void initBackground();
	void handleExitEvent(sf::Event& event);
	void handleControlsEvent(sf::Event& event);
	void drawControls(std::shared_ptr<sf::RenderWindow> window);
	void updateControls(float deltaSeconds);

public:
	MapMenuState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~MapMenuState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif