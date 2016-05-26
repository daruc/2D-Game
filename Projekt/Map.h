#ifndef MAP_H
#define MAP_H
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

class Map
{
private:
	sf::Vector2f player;
	sf::Vector2f finish;
	std::list<std::shared_ptr<sf::ConvexShape>> shapes;
	sf::Vector2f viewOffset;
public:
	inline void setViewOffset(sf::Vector2f vec) { viewOffset = vec; }
	void moveView(sf::Vector2f vec);
	void addShape(std::list<sf::Vector2f> points);
	void removeLast();
	void draw(sf::RenderWindow & window);
	inline sf::Vector2f getPlayerPosition() { return player; }
	inline sf::Vector2f getFinishPosition() { return finish; }
	void setPlayerPosition(float x, float y);
	void setFinishPosition(float x, float y);
};

#endif