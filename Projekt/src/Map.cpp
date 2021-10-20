#include "Map.h"
#include "Enemy.h"
#include <utility>
#include <cstring>


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
	for (std::shared_ptr<sf::RectangleShape> bullet : bullets)
	{
		window->draw(*bullet);
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

std::vector<char> Map::toBinary( ) const
{
	size_t nShapes = shapes.size();

	sf::Vector2f player_position = player.getPosition();
	sf::Vector2f finish_postiion = finish.getPosition();
	size_t size = sizeof(type) 
		+ sizeof(player_position.x)
		+ sizeof(player_position.y)
		+ sizeof(finish_postiion.x)
		+ sizeof(finish_postiion.y)
		+ sizeof(nShapes);	//type + player and finish position + nShapes

	auto begin = shapes.begin();
	auto end = shapes.end();
	for (auto it = begin; it != end; ++it)
	{
		size += sizeof(int) + sizeof(size_t) + sizeof(float) * 2;	//number of verticles + position + type
		size += (*it)->getPointCount() * sizeof(float) * 2;	//verticles
	}

	//number of enemies
	size += sizeof(enemies.size());
	auto begin_enemies = enemies.begin();
	auto end_enemies = enemies.end();
	for (auto it = begin_enemies; it != end_enemies; ++it)
	{
		size += sizeof(float)*2;	//enemy.x + enemy.y positions
	}

	std::vector<char> bytes(size);
	char * ptr = bytes.data();
	memcpy(ptr, &type, sizeof(type));
	ptr += sizeof(type);
	memcpy(ptr, &player_position.x, sizeof(player_position.x));
	ptr += sizeof(player_position.x);
	memcpy(ptr, &player_position.y, sizeof(player_position.y));
	ptr += sizeof(player_position.y);
	memcpy(ptr, &finish_postiion.x, sizeof(finish_postiion.x));
	ptr += sizeof(finish_postiion.x);
	memcpy(ptr, &finish_postiion.y, sizeof(finish_postiion.y));
	ptr += sizeof(finish_postiion.y);
	memcpy(ptr, &nShapes, sizeof(nShapes));
	ptr += sizeof(nShapes);
	for (auto it = begin; it != end; ++it)
	{
		int shape_type = (int)(*it)->getType();
		memcpy(ptr, &shape_type, sizeof(shape_type));
		ptr += sizeof(shape_type);
		size_t count = (*it)->getPointCount();
		memcpy(ptr, &count, sizeof(count));
		ptr += sizeof(count);
		sf::Vector2f shape_position = (*it)->getPosition();
		memcpy(ptr, &shape_position.x, sizeof(shape_position.x));
		ptr += sizeof(shape_position.x);
		memcpy(ptr, &shape_position.y, sizeof(shape_position.y));
		ptr += sizeof(shape_position.y);
		for (size_t j = 0; j < count; ++j)
		{
			sf::Vector2f point = (*it)->getPoint(j);
			memcpy(ptr, &point.x, sizeof(point.x));
			ptr += sizeof(point.x);
			memcpy(ptr, &point.y, sizeof(point.y));
			ptr += sizeof(point.y);
		}
	}

	int nEnemies = enemies.size();
	memcpy(ptr, &nEnemies, sizeof(nEnemies));
	if (nEnemies > 0)
	{
		ptr += sizeof(nEnemies);
		for (auto it = begin_enemies; it != end_enemies; ++it)
		{
			sf::Vector2f position = (*it)->getPosition();
			memcpy(ptr, &position.x, sizeof(position.x));
			ptr += sizeof(position.x);
			memcpy(ptr, &position.y, sizeof(position.y));
			ptr += sizeof(position.y);
		}
	}

	return bytes;
}

void Map::fromBinary(int size, char * bytes)
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
	sf::Vector2f player_position;
	memcpy(&player_position.x, ptr, sizeof(player_position.x));
	ptr += sizeof(player_position.x);
	memcpy(&player_position.y, ptr, sizeof(player_position.y));
	ptr += sizeof(player_position.y);
	player.setPosition(player_position);

	sf::Vector2f finish_position;
	memcpy(&finish_position.x, ptr, sizeof(finish_position.x));
	ptr += sizeof(finish_position.x);
	memcpy(&finish_position.y, ptr, sizeof(finish_position.y));
	ptr += sizeof(finish_position.y);
	finish.setPosition(finish_position);

	memcpy(&nShapes, ptr, sizeof(nShapes));
	ptr += sizeof(nShapes);
	for (int i = 0; i < nShapes; ++i)
	{
		int shape_type;
		memcpy(&shape_type, ptr, sizeof(type));
		ptr += sizeof(type);

		memcpy(&verticles, ptr, sizeof(verticles));
		ptr += sizeof(verticles);

		memcpy(&position.x, ptr, sizeof(position.x));
		ptr += sizeof(position.x);

		memcpy(&position.y, ptr, sizeof(position.y));
		ptr += sizeof(position.y);

		std::shared_ptr<MapShape> shape = std::make_shared<MapShape>();
		shape->setPosition(position);
		shape->setPointCount(verticles);	//error here
		shape->setType((MapShape::Type) shape_type);

		for (int j = 0; j < verticles; ++j)
		{
			sf::Vector2f vex;
			memcpy(&vex.x, ptr, sizeof(vex.x));
			ptr += sizeof(vex.x);
			memcpy(&vex.y, ptr, sizeof(vex.y));
			ptr += sizeof(vex.y);
			shape->setPoint(j, vex);
		}
		shapes.push_back(shape);
		
	}
	memcpy(&nEnemies, ptr, sizeof(nEnemies));
	ptr += sizeof(nEnemies);
	for (int i = 0; i < nEnemies; ++i)
	{
		memcpy(&position.x, ptr, sizeof(position.x));
		ptr += sizeof(position.x);
		memcpy(&position.y, ptr, sizeof(position.y));
		ptr += sizeof(position.y);

		auto enemy = std::make_shared<Enemy>();
		enemy->setPosition(position);
		enemy->update(0);
		enemies.push_back(enemy);
	}

	this->type = map_type;
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
	std::shared_ptr<Blood> new_blood = std::make_shared<Blood>(bloodPosition);
	blood.push_back(new_blood);
}

void Map::update(float deltaSeconds)
{
	updateBlood(deltaSeconds);
	player.update(deltaSeconds);
	removeOutOfDateBlood();
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