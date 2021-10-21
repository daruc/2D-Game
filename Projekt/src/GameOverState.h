#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include <list>
#include <SFML/Audio.hpp>

#include "GUI/Control.h"
#include "State.h"
#include "Updatable.h"
#include "Drawable.h"


namespace sf
{
	class RenderWindow;
}

class Strings;

class GameOverState : public State
{
private:
	std::list<std::shared_ptr<Control>> controls;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text title;
	sf::Text result;
	sf::Text time;

	sf::SoundBuffer sound_buffer;
	sf::Sound sound;

	void handleExitEvent(sf::Event & event);
	void handleControlsEvents(sf::Event & event);
	void drawControls(std::shared_ptr<sf::RenderWindow> window);
	void createBackButton(Strings* strings);
	void initWin(Strings* strings, float seconds);
	void initDefeated(Strings* strings);

public:
	GameOverState(std::shared_ptr<sf::RenderWindow> window, bool isWin, float seconds = 0.0f);
	virtual ~GameOverState();
	virtual void handleEvents();
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif
