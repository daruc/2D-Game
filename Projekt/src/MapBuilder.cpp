#include <fstream>
#include <iostream>
#include "MapBuilder.h"


MapBuilder::MapBuilder(std::shared_ptr<sf::RenderWindow> window)
{
	map = std::make_shared<Map>(window);
}
bool MapBuilder::loadFromFile(std::string filename)
{
	std::ifstream fin;
	fin.open(filename, std::fstream::out | std::fstream::binary);
	if (!fin.is_open())
	{
		std::cout << "Cannot open map file.\n";
		return false;
	}
	fin.seekg(0, fin.end);
	int size = fin.tellg();
	fin.seekg(0, fin.beg);
	std::vector<char> bytes(size);
	fin.read(bytes.data(), size);
	map->fromBinary(bytes.data());

	return true;
}

std::shared_ptr<Map> MapBuilder::get()
{
	return map;
}