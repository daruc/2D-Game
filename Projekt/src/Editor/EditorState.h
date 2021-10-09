#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include <list>
#include <stack>
#include <vector>
#include <memory>

#include <SFML\Graphics.hpp>

#include "../State.h"
#include "../Map.h"
#include "../Textures.h"
#include "../Drawable.h"
#include "../Updatable.h"
#include "../Strings.h"
#include "../GUI/SelectableButtonGroup.h"
#include "../GUI/Control.h"
#include "EditorMouseMode.h"
#include "EditorMap.h"


class EditorState : public State
{
private:
	SelectableButtonGroup groundTypesButtonGroup;
	std::shared_ptr<SelectableButton> type1_button;
	std::shared_ptr<SelectableButton> type2_button;
	std::shared_ptr<SelectableButton> type3_button;
	std::shared_ptr<SelectableButton> type4_button;

	std::vector<std::shared_ptr<Control>> controls;

	std::stack<std::string> undo_stack;
	std::shared_ptr<EditorMouseMode> mouse_mode;

	EditorMap editor_map;

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
	void initDefaultMouseMode();
	void handleControlsEvent(sf::Event& event);
	void handleMouse(sf::Event & event);
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