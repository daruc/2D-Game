#ifndef CONTROLS_STATE_H
#define CONTROLS_STATE_H

#include <memory>
#include <list>
#include <tuple>
#include "State.h"
#include "Control.h"
#include "KeyField.h"


class Strings;
typedef std::tuple<sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key> Keys;

class ControlsState : public State
{
private:
	sf::Font font;
	sf::Text title;
	sf::RectangleShape background;

	std::vector<std::shared_ptr<Control>> controls;

	std::shared_ptr<KeyField> left_field;
	std::shared_ptr<KeyField> right_field;
	std::shared_ptr<KeyField> crouch_field;
	std::shared_ptr<KeyField> jump_field;

	void save();
	Keys load();

	void initRightField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center, Strings* strings);
	void initCrouchField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center, Strings* strings);
	void initJumpField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center, Strings* strings);
	void initSaveButton(std::shared_ptr<sf::RenderWindow>& window, float center, Strings* strings);
	void loadFont();
	void initTitle(Strings* strings);
	void initBackground(std::shared_ptr<sf::RenderWindow>& window);
	void initLeftField(std::shared_ptr<sf::RenderWindow>& window, Keys& keys, float center, Strings* strings);
	void initBack(std::shared_ptr<sf::RenderWindow>& window, Strings* strings);

public:
	ControlsState(std::shared_ptr<sf::RenderWindow> window);

	virtual ~ControlsState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif
