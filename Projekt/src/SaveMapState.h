#ifndef SAVE_MAP_STATE
#define SAVE_MAP_STATE

#include <list>

#include <SFML/Graphics.hpp>

#include "GUI/Control.h"
#include "State.h"


class Map;
class TextField;
class Strings;

class SaveMapState : public State
{
private:
	sf::RectangleShape background;
	std::vector<std::shared_ptr<Control>> controls;
	std::shared_ptr<Map> map;
	sf::Font font;
	sf::Text title;
	std::shared_ptr<TextField> text_field;

	void save(sf::String filename);
	sf::Vector2f getScreenCenter(std::shared_ptr<sf::RenderWindow> window) const;
	void createTextField(std::shared_ptr<sf::RenderWindow> window);
	void createSaveButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void createEditorButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void initTitle(Strings* strings);
	void initBackground(std::shared_ptr<sf::RenderWindow> window);
	void handleExitEvent(sf::Event& event);
	void handleControlsEvents(sf::Event& event);
	void drawControls(std::shared_ptr<sf::RenderWindow> window);

public:
	SaveMapState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~SaveMapState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> renderWindow) override;
};

#endif
