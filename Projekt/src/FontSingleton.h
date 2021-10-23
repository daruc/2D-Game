#ifndef FONT_SINGLETON_H
#define FONT_SINGLETON_H

#include <SFML/Graphics.hpp>

class FontSingleton
{
protected:
	sf::Font font;

	FontSingleton();

public:
	static FontSingleton* getInstance();
	const sf::Font& getFont() const;
};

#endif