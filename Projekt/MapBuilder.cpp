#include <fstream>
#include <iostream>
#include "MapBuilder.h"

MapBuilder::MapBuilder()
{
	map = std::make_shared<Map>();
}
void MapBuilder::loadFromFile(std::wstring filename)
{
	char * bytes;
	std::ifstream fin;
	fin.open(filename, std::fstream::out | std::fstream::binary);
	if (!fin.is_open())
	{
		std::cout << "Cannot open map file.\n";
	}
	fin.seekg(0, fin.end);
	int size = fin.tellg();
	fin.seekg(0, fin.beg);
	bytes = new char[size];
	fin.read(bytes, size);
	map->fromBinary(size, bytes);
	delete[] bytes;
}
std::shared_ptr<Map> MapBuilder::get()
{
	return map;
}