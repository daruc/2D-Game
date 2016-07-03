#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <memory>
#include "State.h"
#include "Map.h"
#include "Textures.h"
#include "Physics.h"

class GameState : public State
{
private:
	sf::Sprite cursor;
	std::shared_ptr<Map> map;
	Textures textures;
	sf::RectangleShape player;
	sf::RectangleShape finish;
	Physics physics;
	sf::View view;

	sf::Clock clock;
	sf::Font font;
	sf::Text txtTime;
public:
	GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~GameState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif
