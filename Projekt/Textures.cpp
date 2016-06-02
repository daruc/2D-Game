#include <iostream>
#include "Textures.h"


void Textures::loadCursor()
{
	if (!cursor.loadFromFile("graphics/cursor.png"))
	{
		std::cout << "Cannot load cursor image.\n";
	}
}

void Textures::loadMapType(int type)
{
	if (type == 1)
	{
		std::cout << "Textures type = 1\n";
		

		sf::Image image;
		if (!image.loadFromFile("graphics/ground_1.png"));
		{	
			std::cout << "Cannot load ground_1.png image.\n";
		}

		std::cout << "Texture size (" << image.getSize().x << ", " << image.getSize().y << ")\n";
		ground.loadFromImage(image);
		ground.setRepeated(true);
	}
}
