#include <iostream>
#include "FontSingleton.h"


namespace
{
	const char* FONT_FILE = "font.ttf";
}

FontSingleton::FontSingleton()
{
	if (font.loadFromFile(FONT_FILE))
	{
		std::cout << "Font has been loaded." << std::endl;
	}
	else
	{
		std::cout << "Failed to load font." << std::endl;
	}
}

FontSingleton* FontSingleton::getInstance()
{
	static FontSingleton instance;
	return &instance;
}

const sf::Font& FontSingleton::getFont() const
{
	return font;
}