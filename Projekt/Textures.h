#ifndef TEXTURES_H
#define TEXTURES_H
#include <SFML/Graphics.hpp>

class Textures
{
private:
	sf::Texture cursor;
	sf::Texture ground;
	sf::Texture clock;
	sf::Texture health_0;
	sf::Texture health_1;
	sf::Texture health_2;
	sf::Texture health_3;
	sf::Texture gun_gui;
	sf::Texture finish;
public:
	void loadCursor();
	void loadHealth();
	void loadClock();
	void loadGunGui();
	void loadFinish();
	void loadMapType(int type);
	inline sf::Texture* getCursor() { return &cursor; }
	inline sf::Texture* getGround() { return &ground; }
	inline sf::Texture* getClock() { return &clock; }
	inline sf::Texture* getGunGui() { return &gun_gui; }
	inline sf::Texture* getFinish() { return &finish; }
	sf::Texture* getHealth(int n = 0);
};

#endif