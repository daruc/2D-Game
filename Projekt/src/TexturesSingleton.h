#ifndef TEXTURES_SINGLETON_H
#define TEXTURES_SINGLETON_H

#include <optional>
#include <string>

#include <SFML/Graphics.hpp>


class TexturesSingleton
{
protected:
	std::unique_ptr<sf::Texture> cursor;
	std::unique_ptr<sf::Texture> ground;
	std::unique_ptr<sf::Texture> clock;
	std::unique_ptr<sf::Texture> health_0;
	std::unique_ptr<sf::Texture> health_1;
	std::unique_ptr<sf::Texture> health_2;
	std::unique_ptr<sf::Texture> health_3;
	std::unique_ptr<sf::Texture> gun_gui;
	std::unique_ptr<sf::Texture> finish;
	std::unique_ptr<sf::Texture> tick;

	TexturesSingleton();
	std::unique_ptr<sf::Texture> makeUniqueTexture() const;
	void loadTexture(sf::Texture* texture, std::string filename) const;
	void release(std::unique_ptr<sf::Texture>& texture);
	void loadGroundTexture(int type);

public:
	void loadCursor();
	void loadTick();
	void loadHealth();
	void loadClock();
	void loadGunGui();
	void loadFinish();
	void loadMapType(int type);
	sf::Texture* getCursor();
	sf::Texture* getGround();
	sf::Texture* getClock();
	sf::Texture* getGunGui();
	sf::Texture* getFinish();
	sf::Texture* getTick();
	sf::Texture* getHealth(int n = 0);
	void releaseAll();
	static TexturesSingleton* getInstance();
};

#endif