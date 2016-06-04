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
	sf::Image image;
	if (type == 1)
	{
		std::cout << "Textures type = 1\n";
		

		
		if (!image.loadFromFile("graphics/ground_1.png"));
		{	
			std::cout << "Cannot load ground_1.png image.\n";
		}

		std::cout << "Texture size (" << image.getSize().x << ", " << image.getSize().y << ")\n";
	}
	else if (type == 2)
	{
		std::cout << "Textures type = 2\n";

		if (!image.loadFromFile("graphics/ground_2.png"));
		{
			std::cout << "Cannot load ground_2.png image.\n";
		}

		std::cout << "Texture size (" << image.getSize().x << ", " << image.getSize().y << ")\n";
	}
	else if (type == 3)
	{
		std::cout << "Textures type = 3\n";

		if (!image.loadFromFile("graphics/ground_3.png"));
		{
			std::cout << "Cannot load ground_3.png image.\n";
		}

		std::cout << "Texture size (" << image.getSize().x << ", " << image.getSize().y << ")\n";
	}
	else if (type == 4)
	{
		std::cout << "Textures type = 4\n";

		if (!image.loadFromFile("graphics/ground_4.png"));
		{
			std::cout << "Cannot load ground_4.png image.\n";
		}

		std::cout << "Texture size (" << image.getSize().x << ", " << image.getSize().y << ")\n";
	}
	ground.loadFromImage(image);
	ground.setRepeated(true);
}
