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
#include "Strings.h"
#include "EditorMouseMode.h"
#include "SelectableButtonGroup.h"


class EditorState : public State
{
private:
	std::shared_ptr<SelectableButton> type1_button;
	std::shared_ptr<SelectableButton> type2_button;
	std::shared_ptr<SelectableButton> type3_button;
	std::shared_ptr<SelectableButton> type4_button;

	SelectableButtonGroup groundTypesButtonGroup;
	std::vector<std::shared_ptr<Control>> controls;
	std::shared_ptr<Map> map;
	std::list<sf::Vector2f> points;
	sf::View view;

	Textures textures;

	sf::RectangleShape background;

	sf::RectangleShape start;
	std::vector<std::shared_ptr<sf::RectangleShape>> enemies;
	sf::RectangleShape finish;

	std::stack<std::string> undo_stack;
	std::shared_ptr<EditorMouseMode> mouse_mode;

	void createButtons(Strings* strings);
	void createSaveButton(Strings* strings);
	void createLoadButton(Strings* strings);
	void createPlayerButton(Strings* strings);
	void createFinishButton(Strings* strings);
	void createGroundButton(Strings* strings);
	void createFireButton(Strings* strings);
	void createEnemyButton(Strings* strings);
	void createType1Button(Strings* strings);
	void createType2Button(Strings* strings);
	void createType3Button(Strings* strings);
	void createType4Button(Strings* strings);
	void createBackButton(Strings* strings);
	void createMenuButton(Strings* strings);
	void initStart();
	void initFinish();
	void handleMouse(sf::Event & event);
	void moveAllPoints(float x, float y);
	void parseAndExecuteRemoveShape(std::string command);

public:
	EditorState(std::shared_ptr<sf::RenderWindow> window);
	EditorState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~EditorState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void addPoint(sf::Vector2f point);
	size_t getPointsCount() const;
	void pushUndoAction(sf::String action);
	void addGroundShape();
	void addFireShape();
	std::list<sf::Vector2f> getPoints() const;
	void clearPoints();
	sf::Vector2f getPlayerPosition() const;
	void setPlayerPosition(sf::Vector2f newPosition);
	sf::Vector2f getFinishPosition() const;
	void setFinishPosition(sf::Vector2f newPosition);
	void addEnemy(sf::Vector2f position);
};

#endif