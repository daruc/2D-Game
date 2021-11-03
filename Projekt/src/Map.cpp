#include <utility>
#include <cstring>

#include "Map.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Blood.h"


Map::Map(std::shared_ptr<sf::RenderWindow> window)
	: window(window), player(window)
{
	type = 1;
	player.update(0);
}

void Map::setGroundTexture(sf::Texture * texture)
{
	for (std::shared_ptr<MapShape> shape : shapes)
	{
		if (shape->getType() == MapShape::GROUND)
		{
			setGroundTexture(shape, texture);
		}
		else if (shape->getType() == MapShape::FIRE)
		{
			setFireTexture(shape, texture);
		}
	}
}

void Map::setGroundTexture(std::shared_ptr<MapShape> shape, sf::Texture* texture)
{
	shape->setTexture(texture);
	sf::FloatRect local_bounds = shape->getLocalBounds();
	shape->setTextureRect(sf::IntRect(0, 0, local_bounds.width, local_bounds.height));
}

void Map::setFireTexture(std::shared_ptr<MapShape> shape, sf::Texture* texture)
{
	shape->setFillColor(sf::Color::Yellow);
}

void Map::addShape(std::list<sf::Vector2f> points, sf::Texture* texture)
{
	std::shared_ptr<MapShape> shape = std::make_shared<MapShape>();
	shape->setPointCount(points.size());

	auto begin = points.begin();
	auto end = points.end();

	int index = 0;
	for (auto it = begin; it != end; ++it)
	{
		shape->setPoint(index, *it);
		++index;
	}
	shape->setPosition(viewOffset);
	if (texture != nullptr)
	{
		shape->setTexture(texture);
		sf::FloatRect local_bounds = shape->getLocalBounds();
		shape->setTextureRect(sf::IntRect(0, 0, local_bounds.width, local_bounds.height));
		shape->setType(MapShape::GROUND);
	}
	else
	{
		shape->setFillColor(sf::Color::Yellow);
		shape->setType(MapShape::FIRE);
	}
	
	
	shapes.push_back(shape);
}

void Map::setPlayerPosition(float x, float y)
{
	sf::Vector2f position;
	position.x = x;
	position.y = y;
	player.setPosition(position);
}

void Map::setFinishPosition(float x, float y)
{
	sf::Vector2f position;
	position.x = x;
	position.y = y;
	finish.setPosition(position);
}

void Map::draw(std::shared_ptr<sf::RenderWindow> window)
{
	//draw ground
	for (std::shared_ptr<MapShape> shape : shapes)
	{
		window->draw(*shape);
	}

	// draw player
	player.draw(window);

	// draw finish
	finish.draw(window);

	//draw bullets
	for (std::shared_ptr<Bullet> bullet : bullets)
	{
		bullet->draw(window);
	}

	// draw enemies
	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		enemy->draw(window);
	}

	//draw blood
	for (std::shared_ptr<Blood> blood_item : blood)
	{
		blood_item->draw(window);
	}
}

void Map::moveView(sf::Vector2f vec)
{
	viewOffset += vec;
}

void Map::removeLast()
{
	if (!shapes.empty())
	{
		shapes.pop_back();
	}
}

std::vector<char> Map::toBinary() const
{
	std::vector<char> bytes(binarySize());
	char * ptr = bytes.data();
	memcpy(ptr, &type, sizeof(type));
	ptr += sizeof(type);

	writeAndIncrement(ptr, player);
	writeAndIncrement(ptr, finish);

	size_t nShapes = shapes.size();
	memcpy(ptr, &nShapes, sizeof(nShapes));
	ptr += sizeof(nShapes);
	for (std::shared_ptr<MapShape> map_shape : shapes)
	{
		writeAndIncrement(ptr, *map_shape);
	}

	int nEnemies = enemies.size();
	memcpy(ptr, &nEnemies, sizeof(nEnemies));
	ptr += sizeof(nEnemies);
	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		writeAndIncrement(ptr, *enemy);
	}
	
	return bytes;
}

void Map::writeAndIncrement(char*& destination, const Binary& source) const
{
	std::vector<char> bytes = source.toBinary();
	memcpy(destination, bytes.data(), bytes.size());
	destination += bytes.size();
}

void Map::fromBinary(char* bytes)
{
	shapes.clear();
	size_t nShapes;
	size_t verticles;
	int map_type;
	int nEnemies;
	sf::Vector2f position;
	char * ptr = bytes;
	memcpy(&map_type, ptr, sizeof(type));
	ptr += sizeof(type);

	player.fromBinary(ptr);
	ptr += player.binarySize();
	finish.fromBinary(ptr);
	ptr += finish.binarySize();

	memcpy(&nShapes, ptr, sizeof(nShapes));
	ptr += sizeof(nShapes);
	for (int i = 0; i < nShapes; ++i)
	{
		auto shape = std::make_shared<MapShape>();
		shape->fromBinary(ptr);
		ptr += shape->binarySize();
		shapes.push_back(shape);
	}
	memcpy(&nEnemies, ptr, sizeof(nEnemies));
	ptr += sizeof(nEnemies);
	for (int i = 0; i < nEnemies; ++i)
	{
		auto enemy = std::make_shared<Enemy>();
		enemy->fromBinary(ptr);
		ptr += enemy->binarySize();
		enemies.push_back(enemy);
	}

	this->type = map_type;
}

size_t Map::binarySize() const
{
	size_t size = sizeof(type)
		+ player.binarySize()
		+ finish.binarySize()
		+ sizeof(shapes.size());	//type + player and finish position + nShapes

	for (std::shared_ptr<MapShape> map_shape : shapes)
	{
		size += map_shape->binarySize();
	}

	//number of enemies
	size += sizeof(enemies.size());
	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		size += enemy->binarySize();
	}

	return size;
}

void Map::addEnemy(std::shared_ptr<Enemy> enemy)
{
	sf::Vector2f position = enemy->getPosition();
	position.x += viewOffset.x;
	position.y += viewOffset.y;
	enemy->setPosition(position);
	enemy->update(0);
	enemies.push_back(enemy);
}

void Map::addBlood(sf::Vector2f bloodPosition)
{
	std::shared_ptr<Blood> new_blood = std::make_shared<Blood>(bloodPosition + viewOffset);
	blood.emplace_back(new_blood);
}

void Map::update(float delta_seconds)
{
	updateBlood(delta_seconds);
	player.update(delta_seconds);
	removeOutOfDateBlood();

	for (std::shared_ptr<Bullet> bullet : bullets)
	{
		bullet->update(delta_seconds);
	}
	
	bullets.remove_if(
		[](std::shared_ptr<Bullet> bullet) {
			return bullet->isReadyToRemove();
		}
	);

	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		enemy->update(delta_seconds);
	}
}

void Map::updateBlood(float delta_seconds)
{
	for (std::shared_ptr<Blood> blood_item : blood)
	{
		blood_item->update(delta_seconds);
	}
}

void Map::removeOutOfDateBlood()
{
	auto begin = blood.begin();
	auto end = blood.end();

	for (auto it = begin; it != end; ++it)
	{
		if ((*it)->isReadyToDestroy())
		{
			blood.erase(it);
			break;
		}
	}
}

void Map::popEnemy()
{
	enemies.pop_back();
}

Player * Map::getPlayer()
{
	return &player;
}

Finish* Map::getFinish()
{
	return &finish;
}