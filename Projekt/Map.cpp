#include "Map.h"

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