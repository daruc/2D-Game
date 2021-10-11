#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>
#include <thread>
#include <mutex>

#include <SFML/Audio.hpp>

#include "State.h"
#include "Map.h"
#include "Textures.h"
#include "Physics.h"
#include "Enemy.h"
#include "GUI/HealthPicture.h"


class GameState : public State
{
private:
	sf::Sprite cursor;
	sf::Sprite sprite_clock;
	sf::Sprite sprite_gun;
	HealthPicture health_picture;
	std::shared_ptr<Map> map;
	Textures textures;
	Physics physics;
	sf::View view;

	sf::Clock clock;
	sf::Font font;
	sf::Text txtTime;
	sf::Text bullets;

	//sounds
	sf::SoundBuffer gunshot_buffer;
	sf::SoundBuffer hit_enemy_buffer;
	sf::SoundBuffer knock_buffer;
	sf::SoundBuffer empty_gun_buffer;
	sf::SoundBuffer reload_buffer;
	sf::Sound gunshot;
	sf::Sound hit_enemy;
	sf::Sound knock;
	sf::Sound empty_gun;
	sf::Sound reload;

	//threads
	std::shared_ptr<std::thread> gui_thread;
	std::mutex mtx;
	bool done;

	void loadTextures();
	void loadSounds();
	void loadGunshotSound();
	void loadHitEnemySound();
	void loadKnockSound();
	void loadEmptyGunSound();
	void loadReloadSound();
	bool isClosedEvent(sf::Event & event);
	bool isEscapeEvent(sf::Event & event);
	bool isLeftMouseButtonEvent(sf::Event & event);
	bool isRightMouseButtonEvent(sf::Event & event);
	bool isGunNotEmpty();
	void handleEvent(sf::Event & event);
	void handleEventExit();
	void handleEventExitToMenu();
	void handleEventTryShot();
	void handleEventShoot();
	void handleEventFireEmptyGun();
	void handleEventReload();
	void checkWin();
	void checkDead();

public:
	GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	virtual ~GameState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif
