#include "Map.h"
#include <utility>
#include <cstring>

Map::Map()
{
	type = 1;
}

void Map::setGroundTexture(sf::Texture * texture)
{
	auto begin = shapes.begin();
	auto end = shapes.end();

	for (auto it = begin; it != end; ++it)
	{
		if ((*it)->getType() == MapShape::GROUND)
		{
			(*it)->setTexture(texture);
			sf::FloatRect local_bounds = (*it)->getLocalBounds();
			(*it)->setTextureRect(sf::IntRect(0, 0, local_bounds.width, local_bounds.height));
		}
		else if ((*it)->getType() == MapShape::FIRE)
		{
			(*it)->setFillColor(sf::Color::Yellow);
		}
	}
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
	player.x = x + viewOffset.x;
	player.y = y + viewOffset.y;
}

void Map::setFinishPosition(float x, float y)
{
	finish.x = x + viewOffset.x;
	finish.y = y + viewOffset.y;
}

void Map::draw(sf::RenderWindow & window)
{
	auto begin = shapes.begin();
	auto end = shapes.end();

	for (auto it = begin; it != end; ++it)
	{
		//(*it)->setFillColor(sf::Color::Black);
		window.draw(**it);
	}

	//draw bullets
	auto bulletsBegin = bullets.begin();
	auto bulletsEnd = bullets.end();

	for (auto it = bulletsBegin; it != bulletsEnd; ++it)
	{
		window.draw(**it);
	}
}

void Map::moveView(sf::Vector2f vec)
{
	viewOffset += vec;
}

void Map::removeLast()
{
	if (shapes.size() > 0)
		shapes.pop_back();
}

std::pair<int, char*> Map::toBinary( ) const
{
	size_t size = 24;	//type + player and finish position + nShapes
	size_t nShapes = shapes.size();
	size_t verticles = 0;
	auto begin = shapes.begin();
	auto end = shapes.end();
	for (auto it = begin; it != end; ++it)
	{
		size += 16;	//number of verticles + position + type
		size += (*it)->getPointCount() * 8;	//verticles
		verticles += (*it)->getPointCount();
	}

	char * bytes = new char[size];
	char * ptr = bytes;
	memcpy(ptr, &type, sizeof(type));
	ptr += sizeof(type);
	memcpy(ptr, &player.x, sizeof(player.x));
	ptr += sizeof(player.x);
	memcpy(ptr, &player.y, sizeof(player.y));
	ptr += sizeof(player.y);
	memcpy(ptr, &finish.x, sizeof(finish.x));
	ptr += sizeof(finish.x);
	memcpy(ptr, &finish.y, sizeof(finish.y));
	ptr += sizeof(finish.y);
	memcpy(ptr, &nShapes, sizeof(nShapes));
	ptr += sizeof(nShapes);
	for (auto it = begin; it != end; ++it)
	{
		size_t shape_type = (int)(*it)->getType();
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

	return std::pair<int, char*>(size, bytes);
}

void Map::fromBinary(int size, char * bytes)
{
	shapes.clear();
	size_t nShapes;
	size_t verticles;
	int map_type;
	sf::Vector2f position;
	char * ptr = bytes;
	memcpy(&map_type, ptr, sizeof(type));
	ptr += sizeof(type);
	memcpy(&player.x, ptr, sizeof(player.x));
	ptr += sizeof(player.x);
	memcpy(&player.y, ptr, sizeof(player.y));
	ptr += sizeof(player.y);
	memcpy(&finish.x, ptr, sizeof(finish.x));
	ptr += sizeof(finish.x);
	memcpy(&finish.y, ptr, sizeof(finish.y));
	ptr += sizeof(finish.y);
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
		shape->setPointCount(verticles);
		shape->setType((MapShape::Type) shape_type);
		//shape->setFillColor(sf::Color::Yellow);
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
	this->type = map_type;
}