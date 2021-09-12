#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <list>
#include <SFML\Graphics.hpp>
#include <stack>
#include "State.h"
#include "Control.h"
#include "Map.h"
#include "Textures.h"
#include <vector>
#include <memory>
#include "Drawable.h"
#include "Updatable.h"


class EditorState : public State
{
private:
	enum Item {GROUND, FIRE, PLAYER, FINISH, ENEMY};
	Item selected;
	std::vector<std::shared_ptr<Control>> controls;
	std::shared_ptr<Map> map;
	std::list<sf::Vector2f> points;
	sf::View view;

	Textures textures;

	sf::RectangleShape background;
	sf::RectangleShape selected_type;

	sf::RectangleShape start;
	std::vector<std::shared_ptr<sf::RectangleShape>> enemies;
	sf::RectangleShape finish;

	std::stack<std::string> undo_stack;

	void handleMouse(sf::Event & event);
	void handleMouseModeGround(sf::Event & event);
	void handleMouseModeFire(sf::Event & event);
	void handleMouseModePlayer(sf::Event & event);
	void handleMouseModeEnemy(sf::Event & event);
	void handleMouseModeFinish(sf::Event & event);
	void moveAllPoints(float x, float y);
	void parseAndExecuteRemoveShape(std::string command);

public:
	EditorState(std::shared_ptr<sf::RenderWindow> window);
	EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~EditorState();
	virtual void handleEvents();
	void update() override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif