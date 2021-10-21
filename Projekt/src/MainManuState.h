#ifndef MAIN_MENU_STATE
#define MAIN_MENU_STATE

#include <list>
#include <memory>

#include "GUI/Control.h"

#include "State.h"
#include "App.h"


class Strings;

class MainMenuState : public State
{
private:
	std::vector<std::shared_ptr<Control>> controls;

	sf::Vector2f getScreenCenter(std::shared_ptr<sf::RenderWindow> window) const;
	void createNewGameButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void createControlsButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void createEditorButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void createExitButton(std::shared_ptr<sf::RenderWindow> window, Strings* strings);
	void handleExitEvent(sf::Event& event);
	void handleControlsEvent(sf::Event& event);
	void drawControls(std::shared_ptr<sf::RenderWindow> window);

public:
	MainMenuState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~MainMenuState();
	virtual void handleEvents();
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};


#endif
