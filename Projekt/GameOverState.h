#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H
#include <list>
#include "Control.h"
#include "State.h"

class GameOverState : public State
{
private:
	std::list<std::shared_ptr<Control>> controls;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text title;
public:
	GameOverState(std::shared_ptr<sf::RenderWindow> window);
	virtual ~GameOverState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif
