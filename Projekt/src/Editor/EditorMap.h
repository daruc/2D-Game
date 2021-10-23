#ifndef EDITOR_MAP_H
#define EDITOR_MAP_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "../Drawable.h"
#include "EditorMap.h"


namespace sf
{
	class Event;
}

enum class Space
{
	SCREEN,
	MAP
};

class Map;

class EditorMap : public Drawable
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	sf::View view;
	std::shared_ptr<Map> map;
	std::list<sf::Vector2f> points;

	sf::RectangleShape background;
	sf::RectangleShape finish;

	void initBackground();

	void scrollRight();
	void moveAllPoints(float x, float y);
	void scrollLeft();
	void scrollDown();
	void scrollUp();
	sf::Vector2f convertScreenToMap(sf::Vector2f position) const;
	sf::Vector2f convertMapToScreen(sf::Vector2f position) const;
	void reloadMapTypeTextures();

public:
	EditorMap(std::shared_ptr<sf::RenderWindow> window);
	EditorMap(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	void handleEvent(sf::Event & event);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void addPoint(sf::Vector2f point, Space space = Space::SCREEN);
	size_t getPointsCount() const;
	void addGroundShape();
	void addFireShape();
	std::list<sf::Vector2f> getPoints() const;
	void clearPoints();
	sf::Vector2f getPlayerPosition(Space space = Space::MAP) const;
	void setPlayerPosition(sf::Vector2f newPosition, Space space = Space::MAP);
	sf::Vector2f getFinishPosition(Space space = Space::MAP) const;
	void setFinishPosition(sf::Vector2f newPosition, Space space = Space::MAP);
	void addEnemy(sf::Vector2f position);
	std::shared_ptr<Map> getMap();
	void setMapType1();
	void setMapType2();
	void setMapType3();
	void setMapType4();
	sf::Vector2f popPoint(Space space = Space::SCREEN);
	void popEnemy();
	void removeLast();
};

#endif // !EDITOR_MAP_H
