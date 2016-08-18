#include <iostream>
#include "Textures.h"


void Textures::loadCursor()
{
	if (!cursor.loadFromFile("graphics/cursor.png"))
	{
		std::cout << "Cannot load cursor image.\n";
	}
}

void Textures::loadClock()
{
	if (!clock.loadFromFile("graphics/clock.png"))
	{
		std::cout << "Cannot load clock image.\n";
	}
}


void Textures::loadHealth()
{
	if (!health_0.loadFromFile("graphics/health_0.png"))
	{
		std::cout << "Cannot load health 0 image.\n";
	}

	if (!health_1.loadFromFile("graphics/health_1.png"))
	{
		std::cout << "Cannot load health 1 image.\n";
	}

	if (!health_2.loadFromFile("graphics/health_2.png"))
	{
		std::cout << "Cannot load health 2 image.\n";
	}

	if (!health_3.loadFromFile("graphics/health_3.png"))
	{
		std::cout << "Cannot load health 3 image.\n";
	}
}

void Textures::loadGunGui()
{
	if (!gun_gui.loadFromFile("graphics/gun_gui.png"))
	{
		std::cout << "Cannot load gun_gui.png image.\n";
	}
}

void Textures::loadFinish()
{
	if (!finish.loadFromFile("graphics\\finish.png"))
	{
		std::cout << "Cannot load finish.png image.\n";
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

sf::Texture* Textures::getHealth(int n)
{
	switch (n)
	{
	case 0:
		return &health_0;
	case 1:
		return &health_1;
	case 2:
		return &health_2;
	case 3:
		return &health_3;

	}
}
