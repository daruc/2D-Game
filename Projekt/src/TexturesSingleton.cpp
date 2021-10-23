#include <iostream>
#include <sstream>
#include "TexturesSingleton.h"


TexturesSingleton::TexturesSingleton()
{

}

std::unique_ptr<sf::Texture> TexturesSingleton::makeUniqueTexture() const
{
	return std::make_unique<sf::Texture>();
}

void TexturesSingleton::loadCursor()
{
	if (!cursor)
	{
		cursor = std::move(makeUniqueTexture());
		loadTexture(cursor.get(), "graphics/cursor.png");
	}
}

void TexturesSingleton::loadClock()
{
	if (!clock)
	{
		clock = std::move(makeUniqueTexture());
		loadTexture(clock.get(), "graphics/clock.png");
	}
}

void TexturesSingleton::loadHealth()
{
	if (!health_0)
	{
		health_0 = std::move(makeUniqueTexture());
		loadTexture(health_0.get(), "graphics/health_0.png");
	}

	if (!health_1)
	{
		health_1 = std::move(makeUniqueTexture());
		loadTexture(health_1.get(), "graphics/health_1.png");
	}

	if (!health_2)
	{
		health_2 = std::move(makeUniqueTexture());
		loadTexture(health_2.get(), "graphics/health_2.png");
	}

	if (!health_3)
	{
		health_3 = std::move(makeUniqueTexture());
		loadTexture(health_3.get(), "graphics/health_3.png");
	}
}

void TexturesSingleton::loadGunGui()
{
	if (!gun_gui)
	{
		gun_gui = std::move(makeUniqueTexture());
		loadTexture(gun_gui.get(), "graphics/gun_gui.png");
	}
}

void TexturesSingleton::loadFinish()
{
	if (!finish)
	{
		finish = std::move(makeUniqueTexture());
		loadTexture(finish.get(), "graphics\\finish.png");
	}
}

void TexturesSingleton::loadTick()
{
	if (!tick)
	{
		tick = std::move(makeUniqueTexture());
		loadTexture(tick.get(), "graphics\\tick.png");
	}
}

void TexturesSingleton::loadMapType(int type)
{
	loadGroundTexture(type);
}

void TexturesSingleton::loadGroundTexture(int type)
{
	std::stringstream file_name_stream;
	file_name_stream << "graphics\\ground_";
	file_name_stream << type << ".png";

	ground = std::move(makeUniqueTexture());
	loadTexture(ground.get(), file_name_stream.str().c_str());
	ground->setRepeated(true);
}

sf::Texture* TexturesSingleton::getHealth(int n)
{
	switch (n)
	{
	case 0:
		return health_0.get();
	case 1:
		return health_1.get();
	case 2:
		return health_2.get();
	case 3:
		return health_3.get();

	}
}

void TexturesSingleton::releaseAll()
{
	release(cursor);
	release(ground);
	release(clock);
	release(health_0);
	release(health_1);
	release(health_2);
	release(health_3);
	release(gun_gui);
	release(finish);
	release(tick);
}

void TexturesSingleton::release(std::unique_ptr<sf::Texture>& texture)
{
	if (texture)
	{
		texture.reset();
		std::cout << "Texture has been released\n";
	}
}

TexturesSingleton* TexturesSingleton::getInstance()
{
	static TexturesSingleton instance;
	return &instance;
}

void TexturesSingleton::loadTexture(sf::Texture* texture, std::string filename) const
{
	if (texture->loadFromFile(filename.c_str()))
	{
		std::cout << "Texture loaded: " << filename << std::endl;
	}
	else
	{
		std::cout << "Error during loading texture: " << filename << std::endl;
	}
}

sf::Texture* TexturesSingleton::getCursor()
{ 
	if (!cursor)
	{
		std::cout << "Failed to get texture: cursor\n";
	}
	return cursor.get();
}

sf::Texture* TexturesSingleton::getGround()
{
	if (!ground)
	{
		std::cout << "Failed to get texture: ground\n";
	}
	return ground.get();
}

sf::Texture* TexturesSingleton::getClock()
{ 
	if (!clock)
	{
		std::cout << "Failed to get texture: clock\n";
	}
	return clock.get(); 
}

sf::Texture* TexturesSingleton::getGunGui()
{ 
	if (!gun_gui)
	{
		std::cout << "Failed to get texture: gun_gui\n";
	}
	return gun_gui.get();
}

sf::Texture* TexturesSingleton::getFinish()
{ 
	if (!finish)
	{
		std::cout << "Failed to get texture: finish\n";
	}
	return finish.get();
}

sf::Texture* TexturesSingleton::getTick()
{
	if (!tick)
	{
		std::cout << "Failed to get texture: tick\n";
	}
	return tick.get(); 
}