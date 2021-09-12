#include <fstream>
#include <iostream>
#include "MapBuilder.h"


MapBuilder::MapBuilder()
{
	map = std::make_shared<Map>();
}
bool MapBuilder::loadFromFile(std::wstring filename)
{
	char * bytes;
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
	bytes = new char[size];
	fin.read(bytes, size);
	map->fromBinary(size, bytes);
	delete[] bytes;

	return true;
}

std::shared_ptr<Map> MapBuilder::get()
{
	return map;
}