#ifndef LOAD_MAP_STATE
#define LOAD_MAP_STATE

#include <list>

#include "GUI/Control.h"

#include "State.h"
#include "Map.h"
#include "Drawable.h"
#include "Updatable.h"


class TextField;
class Strings;

class LoadMapState : public State
{
private:
	sf::RectangleShape background;
	std::shared_ptr<Map> prev_map;
	std::vector<std::shared_ptr<Control>> controls;
	std::shared_ptr<TextField> text_field;
	sf::Text title;

	sf::Vector2f getScreenCenter(std::shared_ptr<sf::RenderWindow> window) const;
	void handleExitEvent(sf::Event& event);
	void handleControlsEvents(sf::Event& event);
	void drawControls(std::shared_ptr<sf::RenderWindow> window);
	void createTextField(std::shared_ptr<sf::RenderWindow> window);
	void createLoadButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void createEditorButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void initTitle(Strings* strings);
	void initBackground();

public:
	LoadMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~LoadMapState();
	virtual void handleEvents();
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif