#include "Map.h"
#include <utility>
#include <cstring>

void Map::addShape(std::list<sf::Vector2f> points)
{
	std::shared_ptr<sf::ConvexShape> shape = std::make_shared<sf::ConvexShape>();
	shape->setFillColor(sf::Color::Yellow);
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
	size_t size = 20;	//player and finish position + nShapes
	size_t nShapes = shapes.size();
	size_t verticles = 0;
	auto begin = shapes.begin();
	auto end = shapes.end();
	for (auto it = begin; it != end; ++it)
	{
		size += 4;	//number of verticles
		size += (*it)->getPointCount() * 8;	//verticles
		verticles += (*it)->getPointCount();
	}

	char * bytes = new char[size];
	char * ptr = bytes;
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
		size_t count = (*it)->getPointCount();
		memcpy(ptr, &count, sizeof(count));
		ptr += sizeof(count);
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
	int nShapes;
	int verticles;
	char * ptr = bytes;
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
		memcpy(&verticles, ptr, sizeof(verticles));
		ptr += sizeof(verticles);

		std::shared_ptr<sf::ConvexShape> shape = std::make_shared<sf::ConvexShape>();
		shape->setPointCount(verticles);
		shape->setFillColor(sf::Color::Yellow);
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

}