#ifndef MAP_H
#define MAP_H

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Binary.h"
#include "MapShape.h"
#include "Blood.h"
#include "Drawable.h"
#include "Updatable.h"


class Map : public Binary, public Updatable, public Drawable
{
private:
	int type;
	sf::Vector2f player;
	sf::Vector2f finish;
	std::vector<std::shared_ptr<MapShape>> shapes;
	std::list<std::shared_ptr<sf::RectangleShape>> bullets;
	std::list<std::shared_ptr<sf::RectangleShape>> enemies;
	std::list<std::shared_ptr<Blood>> blood;
	sf::Vector2f viewOffset;

	void removeOutOfDateBlood();

public:
	Map();
	inline void setViewOffset(sf::Vector2f vec) { viewOffset = vec; }
	void moveView(sf::Vector2f vec);
	void addShape(std::list<sf::Vector2f> points, sf::Texture* texture);
	void removeLast();
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	inline sf::Vector2f getPlayerPosition() { return player; }
	inline sf::Vector2f getFinishPosition() { return finish; }
	inline sf::Vector2f getViewOffset() const { return viewOffset; }
	inline auto getGroundBegin() { return shapes.begin();  }
	inline auto getGroundEnd() { return shapes.end(); }
	inline auto getEnemiesBegin() { return enemies.begin(); }
	inline auto getEnemiesEnd() { return enemies.end(); }
	inline int getType() { return type; }
	inline void setType(int type) { this->type = type; }
	inline std::list<std::shared_ptr<sf::RectangleShape>>* getBulletsList() { return &bullets; }
	inline std::list<std::shared_ptr<sf::RectangleShape>>* getEnenemiesList() { return &enemies; }
	void setPlayerPosition(float x, float y, bool offset=true);
	void setFinishPosition(float x, float y, bool offset=true);
	void setGroundTexture(sf::Texture * texture);
	void addEnemy(std::shared_ptr<sf::RectangleShape> enemyRect);
	void addBlood(sf::Vector2f bloodPosition);
	void update(float deltaSeconds) override;
	std::vector<char> Map::toBinary() const override;
	void fromBinary(int size, char * bytes) override;

};

#endif