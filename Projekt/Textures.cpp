#include <iostream>
#include "Textures.h"


void Textures::loadCursor()
{
	if (!cursor.loadFromFile("graphics/cursor.png"))
	{
		std::cout << "Cannot load cursor image.\n";
	}
}
