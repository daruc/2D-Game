#ifndef MAP_H
#define MAP_H

#include <list>
#include <memory>
#include <vector>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "Binary.h"
#include "MapShape.h"
#include "Drawable.h"
#include "Updatable.h"
#include "Finish.h"
#include "Player.h"


class Enemy;
class Bullet;
class Blood;

class Map : public Binary, public Updatable, public Drawable
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	int type;
	Player player;
	Finish finish;
	std::vector<std::shared_ptr<MapShape>> shapes;
	std::list<std::shared_ptr<Bullet>> bullets;
	std::list<std::shared_ptr<Enemy>> enemies;
	std::list<std::shared_ptr<Blood>> blood;
	sf::Vector2f viewOffset;

	void removeOutOfDateBlood();
	void updateBlood(float delta_seconds);
	void setGroundTexture(std::shared_ptr<MapShape> shape, sf::Texture* texture);
	void setFireTexture(std::shared_ptr<MapShape> shape, sf::Texture* texture);
	void writeAndIncrement(char*& destination, const Binary& source) const;

public:
	Map(std::shared_ptr<sf::RenderWindow> window);
	inline void setViewOffset(sf::Vector2f vec) { viewOffset = vec; }
	void moveView(sf::Vector2f vec);
	void addShape(std::list<sf::Vector2f> points, sf::Texture* texture);
	void removeLast();
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	inline sf::Vector2f getPlayerPosition() { return player.getPosition(); }
	inline sf::Vector2f getFinishPosition() { return finish.getPosition(); }
	inline sf::Vector2f getViewOffset() const { return viewOffset; }
	inline auto getGroundBegin() { return shapes.begin();  }
	inline auto getGroundEnd() { return shapes.end(); }
	inline auto getEnemiesBegin() { return enemies.begin(); }
	inline auto getEnemiesEnd() { return enemies.end(); }
	inline int getType() { return type; }
	inline void setType(int type) { this->type = type; }
	inline std::list<std::shared_ptr<Bullet>>* getBulletsList() { return &bullets; }
	inline std::list<std::shared_ptr<Enemy>>* getEnenemiesList() { return &enemies; }
	void setPlayerPosition(float x, float y);
	void setFinishPosition(float x, float y);
	void setGroundTexture(sf::Texture * texture);
	void addEnemy(std::shared_ptr<Enemy> enemy);
	void popEnemy();
	void addBlood(sf::Vector2f bloodPosition);
	void update(float delta_seconds) override;
	std::vector<char> Map::toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;
	Player * getPlayer();
	Finish* getFinish();
};

#endif