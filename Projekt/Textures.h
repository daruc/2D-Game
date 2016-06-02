#ifndef TEXTURES_H
#define TEXTURES_H
#include <SFML/Graphics.hpp>

class Textures
{
private:
	sf::Texture cursor;
	sf::Texture ground;
public:
	void loadCursor();
	void loadMapType(int type);
	inline sf::Texture* getCursor() { return &cursor; }
	inline sf::Texture* getGround() { return &ground; }
};

#endif