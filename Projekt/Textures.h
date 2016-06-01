#ifndef TEXTURES_H
#define TEXTURES_H
#include <SFML/Graphics.hpp>

class Textures
{
private:
	sf::Texture cursor;
public:
	void loadCursor();
	inline sf::Texture* getCursor() { return &cursor; }
};

#endif