#include <iostream>

#include <SFML/Window.hpp>

#include "EditorMap.h"
#include "../Enemy.h"
#include "../Map.h"


const float SCROLLING_SPEED = 50.0f;
const float LEFT_MAP_EDGE = 130.0f;

EditorMap::EditorMap(std::shared_ptr<sf::RenderWindow> window)
	: window(window), view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y))
{
	map = std::make_shared<Map>(window);
	initBackground();
	textures.loadMapType(1);
	map->setGroundTexture(textures.getGround());
}

EditorMap::EditorMap(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: window(window), view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y))
{
	this->map = map;
	initBackground();
	reloadMapTypeTextures();
}

void EditorMap::initBackground()
{
	background.setSize(sf::Vector2f(LEFT_MAP_EDGE, window->getSize().y));
	background.setFillColor(sf::Color(0, 0, 100, 255));
}

void EditorMap::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Right:
			scrollRight();
			break;
		case sf::Keyboard::Left:
			scrollLeft();
			break;
		case sf::Keyboard::Down:
			scrollDown();
			break;
		case sf::Keyboard::Up:
			scrollUp();
			break;
		}
	}
}

void EditorMap::draw(std::shared_ptr<sf::RenderWindow> window)
{
	//points
	sf::RectangleShape point;
	point.setFillColor(sf::Color::Green);
	point.setSize(sf::Vector2f(3.0f, 3.0f));

	for (sf::Vector2f point_poisition : points)
	{
		point.setPosition(point_poisition);
		window->draw(point);
	}

	//map
	window->setView(view);
	map->draw(window);

	window->draw(finish);
	window->setView(window->getDefaultView());

	window->draw(background);
}

void EditorMap::scrollRight()
{
	view.move(50.0f, 0.0f);
	map->moveView(sf::Vector2f(50.0f, 0.0f));
	moveAllPoints(-50.0f, 0.0f);
	std::cout << "view.move right\n";
}

void EditorMap::moveAllPoints(float x, float y)
{
	for (sf::Vector2f& point : points)
	{
		point.x += x;
		point.y += y;
	}
}

void EditorMap::scrollLeft()
{
	view.move(-SCROLLING_SPEED, 0.0f);
	map->moveView(sf::Vector2f(-SCROLLING_SPEED, 0.0f));
	moveAllPoints(SCROLLING_SPEED, 0.0f);
	std::cout << "view.move left\n";
}

void EditorMap::scrollDown()
{
	view.move(0.0f, SCROLLING_SPEED);
	map->moveView(sf::Vector2f(0.0f, SCROLLING_SPEED));
	moveAllPoints(0.0f, -SCROLLING_SPEED);
	std::cout << "view.move down\n";
}

void EditorMap::scrollUp()
{
	view.move(0.0f, -50.0f);
	map->moveView(sf::Vector2f(0.0f, -SCROLLING_SPEED));
	moveAllPoints(0.0f, SCROLLING_SPEED);
	std::cout << "view.move up\n";
}

sf::Vector2f EditorMap::convertScreenToMap(sf::Vector2f position) const
{
	return position + map->getViewOffset();
}

sf::Vector2f EditorMap::convertMapToScreen(sf::Vector2f position) const
{
	return position - map->getViewOffset();
}

void EditorMap::addPoint(sf::Vector2f point, Space space)
{
	if (space == Space::MAP)
	{
		point = convertMapToScreen(point);
	}
	points.push_back(point);
}

size_t EditorMap::getPointsCount() const
{
	return points.size();
}

void EditorMap::addGroundShape()
{
	map->addShape(points, textures.getGround());
}

void EditorMap::addFireShape()
{
	map->addShape(points, nullptr);
}

std::list<sf::Vector2f> EditorMap::getPoints() const
{
	return points;
}

void EditorMap::clearPoints()
{
	points.clear();
}

sf::Vector2f EditorMap::getPlayerPosition(Space space) const
{
	sf::Vector2f position = map->getPlayerPosition();
	if (space == Space::SCREEN)
	{
		position = convertMapToScreen(position);
	}
	return position;
}

void EditorMap::setPlayerPosition(sf::Vector2f newPosition, Space space)
{
	if (space == Space::SCREEN)
	{
		newPosition = convertScreenToMap(newPosition);
	}
	map->setPlayerPosition(newPosition.x, newPosition.y);
}

sf::Vector2f EditorMap::getFinishPosition(Space space) const
{
	sf::Vector2f position = map->getFinishPosition();
	if (space == Space::SCREEN)
	{
		position = convertMapToScreen(position);
	}
	return position;
}

void EditorMap::setFinishPosition(sf::Vector2f newPosition, Space space)
{
	if (space == Space::SCREEN)
	{
		newPosition = convertScreenToMap(newPosition);
	}
	map->setFinishPosition(newPosition.x, newPosition.y);
}

void EditorMap::addEnemy(sf::Vector2f position)
{
	auto enemy = std::make_shared<Enemy>();
	enemy->setPosition(position);
	map->addEnemy(enemy);
}

std::shared_ptr<Map> EditorMap::getMap()
{
	return map;
}

void EditorMap::setMapType1()
{
	map->setType(1);
	reloadMapTypeTextures();
}

void EditorMap::setMapType2()
{
	map->setType(2);
	reloadMapTypeTextures();
}

void EditorMap::setMapType3()
{
	map->setType(3);
	reloadMapTypeTextures();
}

void EditorMap::setMapType4()
{
	map->setType(4);
	reloadMapTypeTextures();
}

void EditorMap::reloadMapTypeTextures()
{
	textures.loadMapType(map->getType());
	map->setGroundTexture(textures.getGround());
}

sf::Vector2f EditorMap::popPoint(Space space)
{
	sf::Vector2f point = *points.rbegin();
	points.pop_back();

	if (space == Space::MAP)
	{
		point = convertScreenToMap(point);
	}

	return point;
}

void EditorMap::popEnemy()
{
	map->popEnemy();
}

void EditorMap::removeLast()
{
	map->removeLast();
}
