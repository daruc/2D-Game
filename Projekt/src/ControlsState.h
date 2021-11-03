#ifndef CONTROLS_STATE_H
#define CONTROLS_STATE_H

#include <memory>
#include <list>
#include <tuple>

#include "State.h"
#include "GUI/Control.h"
#include "GUI/KeyField.h"
#include "ControlsManager.h"


class Strings;

class ControlsState : public State
{
private:
	sf::Text title;
	sf::RectangleShape background;
	std::vector<std::shared_ptr<Control>> controls;
	ControlsManager controls_manager;

	std::shared_ptr<KeyField> right_field;
	std::shared_ptr<KeyField> left_field;
	std::shared_ptr<KeyField> jump_field;
	std::shared_ptr<KeyField> crouch_field;

	void initRightField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center, Strings* strings);
	void initCrouchField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center, Strings* strings);
	void initJumpField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center, Strings* strings);
	void initSaveButton(std::shared_ptr<sf::RenderWindow>& window, float center, Strings* strings);
	void initTitle(Strings* strings);
	void initBackground(std::shared_ptr<sf::RenderWindow>& window);
	void initLeftField(std::shared_ptr<sf::RenderWindow>& window, ControlsManager& controls_manager, float center, Strings* strings);
	void initBack(std::shared_ptr<sf::RenderWindow>& window, Strings* strings);
	void handleExitEvent(sf::Event & event);
	void handleControlsEvent(sf::Event event);
	void drawControls(std::shared_ptr<sf::RenderWindow> window);

public:
	ControlsState(std::shared_ptr<sf::RenderWindow> window);

	virtual ~ControlsState();
	virtual void handleEvents();
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif
