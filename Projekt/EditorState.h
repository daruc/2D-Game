#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H
#include <list>
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Control.h"
#include "Map.h"
#include "Textures.h"

class EditorState : public State
{
private:
	enum Item {GROUND, PLAYER, FINISH, ENEMY};
	Item selected;
	std::list<std::shared_ptr<Control>> controls;
	std::shared_ptr<Map> map;
	std::list<sf::Vector2f> points;
	sf::View view;

	Textures textures;

	sf::RectangleShape background;
	sf::RectangleShape selected_type;

	sf::RectangleShape start;
	sf::RectangleShape finish;

	void handleMouse(sf::Event & event);
	void handleMouseModeGround(sf::Event & event);
	void handleMouseModePlayer(sf::Event & event);
	void handleMouseModeFinish(sf::Event & event);
	void moveAllPoints(float x, float y);
public:
	EditorState(std::shared_ptr<sf::RenderWindow> window);
	EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~EditorState();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif