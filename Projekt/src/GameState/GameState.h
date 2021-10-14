#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>
#include <thread>
#include <mutex>
#include <optional>

#include <SFML/Audio.hpp>

#include "../State.h"
#include "../Map.h"
#include "../Textures.h"
#include "../Physics.h"
#include "../Enemy.h"
#include "HealthIndicator.h"
#include "AmmunitionIndicator.h"
#include "TimeIndicator.h"


class GameState : public State
{
private:
	std::optional<size_t> map_index;

	// GUI
	TimeIndicator time_indicator;
	HealthIndicator health_indicator;
	AmmunitionIndicator ammunition_indicator;

	sf::Sprite cursor;
	std::shared_ptr<Map> map;
	Textures textures;
	Physics physics;
	sf::View view;

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

	bool done;

	void loadTextures();
	void loadCursorTextureAndSetOrigin();
	void initView();
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
	sf::Vector2f calculateBulletSource() const;
	sf::Vector2f calculateBulletDirection() const;
	void handleEventFireEmptyGun();
	void handleEventReload();
	void checkWin();
	bool isNotUserMap() const;
	void markMapAsCompleted();
	void checkDead();

public:
	GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map);
	GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map, size_t map_index);
	virtual ~GameState();
	virtual void handleEvents();
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif
