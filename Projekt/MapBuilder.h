#ifndef MAP_BUILDER_H
#define MAP_BUILDER_H

#include <string>
#include "Map.h"

namespace sf
{
	class RenderWindow;
}


class MapBuilder
{
private:
	std::shared_ptr<Map> map;

public:
	MapBuilder(std::shared_ptr<sf::RenderWindow> window);
	bool loadFromFile(std::wstring filename);
	std::shared_ptr<Map> get();
};

#endif