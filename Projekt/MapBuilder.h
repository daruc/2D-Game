#ifndef MAP_BUILDER_H
#define MAP_BUILDER_H
#include <string>
#include "Map.h"

class MapBuilder
{
private:
	std::shared_ptr<Map> map;
public:
	MapBuilder();
	void loadFromFile(std::wstring filename);
	std::shared_ptr<Map> get();
};

#endif