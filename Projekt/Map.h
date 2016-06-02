#ifndef MAP_H
#define MAP_H
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Binary.h"

class Map : public Binary
{
private:
	int type;
	sf::Vector2f player;
	sf::Vector2f finish;
	std::list<std::shared_ptr<sf::ConvexShape>> shapes;
	sf::Vector2f viewOffset;
public:
	Map();
	inline void setViewOffset(sf::Vector2f vec) { viewOffset = vec; }
	void moveView(sf::Vector2f vec);
	void addShape(std::list<sf::Vector2f> points, sf::Texture* texture);
	void removeLast();
	void draw(sf::RenderWindow & window);
	inline sf::Vector2f getPlayerPosition() { return player; }
	inline sf::Vector2f getFinishPosition() { return finish; }
	inline auto getGroundBegin() { return shapes.begin();  }
	inline auto getGroundEnd() { return shapes.end(); }
	inline int getType() { return type; }
	inline void setType(int type) { this->type = type; }
	void setPlayerPosition(float x, float y);
	void setFinishPosition(float x, float y);
	void setGroundTexture(sf::Texture * texture);

	virtual std::pair<int, char*> Map::toBinary() const;
	virtual void fromBinary(int size, char * bytes);

};

#endif