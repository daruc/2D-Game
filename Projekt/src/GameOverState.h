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

public:
	GameOverState(std::shared_ptr<sf::RenderWindow> window, bool isWin, float seconds = 0.0f);
	virtual ~GameOverState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif