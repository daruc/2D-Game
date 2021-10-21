#include <iostream>
#include <sstream>
#include <thread>

#include "GameState.h"
#include "../MapMenuState.h"
#include "../GameOverState.h"
#include "../Utils/Utils.h"
#include "../Enemy.h"


namespace {
	const float BULLET_SOURCE_OFFSET_RADIUS = 27.0f;
	const float BULLET_SOURCE_VERTICAL_OFFSET = -7.0f;
}


GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window), 
	physics(window, map), 
	health_indicator(map->getPlayer()),
	ammunition_indicator(window, map->getPlayer()), 
	time_indicator(window)
{
	done = false;
	this->map = map;
	loadTextures();
	window->setMouseCursorVisible(false);
	initView();
	loadSounds();
}

GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map, size_t map_index)
	: GameState(window, map)
{
	this->map_index = map_index;
}

void GameState::loadTextures()
{
	textures.loadCursor();
	textures.loadFinish();
	textures.loadMapType(map->getType());
	map->setGroundTexture(textures.getGround());
	loadCursorTextureAndSetOrigin();
}

void GameState::loadCursorTextureAndSetOrigin()
{
	cursor.setTexture(*textures.getCursor(), true);
	sf::Vector2f cursor_origin(textures.getCursor()->getSize());
	cursor_origin /= 2.0f;
	cursor.setOrigin(cursor_origin);
}

void GameState::initView()
{
	view.setSize(window->getSize().x, window->getSize().y);
	view.move(map->getPlayer()->getPosition() - view.getCenter());
}

void GameState::loadSounds()
{
	loadGunshotSound();
	loadHitEnemySound();
	loadKnockSound();
	loadEmptyGunSound();
	loadReloadSound();
}

void GameState::loadGunshotSound()
{
	if (!gunshot_buffer.loadFromFile("sounds\\gunshot.wav"))
	{
		std::cout << "Cannot load file gunshot.wav\n";
	}
	gunshot.setBuffer(gunshot_buffer);
}

void GameState::loadHitEnemySound()
{
	if (!hit_enemy_buffer.loadFromFile("sounds\\hit_enemy.wav"))
	{
		std::cout << "Cannot load file hit_enemy.wav\n";
	}
	hit_enemy.setBuffer(hit_enemy_buffer);
	physics.setHitEnemySound(&hit_enemy);
}

void GameState::loadKnockSound()
{
	if (!knock_buffer.loadFromFile("sounds\\knock.wav"))
	{
		std::cout << "Cannot load file knock.wav\n";
	}
	knock.setBuffer(knock_buffer);
	knock.setVolume(50);
	physics.setKnockSound(&knock);
}

void GameState::loadEmptyGunSound()
{
	if (!empty_gun_buffer.loadFromFile("sounds\\empty_gun.wav"))
	{
		std::cout << "Cannnot load file emtpy_gun.wav\n";
	}
	empty_gun.setBuffer(empty_gun_buffer);
	empty_gun.setVolume(50);
}

void GameState::loadReloadSound()
{
	if (!reload_buffer.loadFromFile("sounds\\reload.wav"))
	{
		std::cout << "Cannot load file reload.wav\n";
	}
	reload.setBuffer(reload_buffer);
}

GameState::~GameState()
{

}

void GameState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		handleEvent(event);
	}
}

void GameState::handleEvent(sf::Event & event)
{
	if (isClosedEvent(event))
	{
		handleEventExit();
	}
	else if (isEscapeEvent(event))
	{
		handleEventExitToMenu();
	}
	else if (isLeftMouseButtonEvent(event))
	{
		handleEventTryShot();
	}
	else if (isRightMouseButtonEvent(event))
	{
		handleEventReload();
	}
}

bool GameState::isClosedEvent(sf::Event & event)
{
	return event.type == sf::Event::Closed;
}

bool GameState::isEscapeEvent(sf::Event& event)
{
	return (event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape);
}

bool GameState::isLeftMouseButtonEvent(sf::Event& event)
{
	return (event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Left);
}

bool GameState::isRightMouseButtonEvent(sf::Event & event)
{
	return (event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Right);
}

bool GameState::isGunNotEmpty()
{
	return map->getPlayer()->shoot();
}

void GameState::handleEventExit()
{
	done = true;
	window->close();
}

void GameState::handleEventExitToMenu()
{
	window->setMouseCursorVisible(true);
	done = true;
	State::nextState = std::make_shared<MapMenuState>(window);
}

void GameState::handleEventTryShot()
{
	std::cout << "click fire\n";
	if (isGunNotEmpty())
	{
		handleEventShoot();
	}
	else
	{
		handleEventFireEmptyGun();
	}
}

void GameState::handleEventShoot()
{
	gunshot.play();
	physics.throwBullet(calculateBulletSource(), calculateBulletDirection());
}

sf::Vector2f GameState::calculateBulletSource() const
{
	sf::Vector2f playerPosition = map->getPlayer()->getPosition();
	sf::Vector2f sourceOffset = calculateBulletDirection();

	sourceOffset *= BULLET_SOURCE_OFFSET_RADIUS;
	sourceOffset.y += BULLET_SOURCE_VERTICAL_OFFSET;
	playerPosition += sourceOffset;

	return playerPosition;
}

sf::Vector2f GameState::calculateBulletDirection() const
{
	sf::Vector2f mouse = cursor.getPosition();
	sf::Vector2u resolution = window->getSize();

	sf::Vector2f direction;
	direction.x = mouse.x - resolution.x / 2;
	direction.y = mouse.y - resolution.y / 2;

	normalizeVector(&direction);

	return direction;
}

void GameState::handleEventFireEmptyGun()
{
	empty_gun.play();
}

void GameState::handleEventReload()
{
	std::cout << "click reload\n";
	if (map->getPlayer()->reload())
	{
		reload.play();
	}
}

void GameState::update(float delta_seconds)
{
	//update cursor position
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	cursor.setPosition(sf::Vector2f(mouse.x, mouse.y));

	//calculate physics
	physics.simulate();

	//set camera
	view.setCenter(map->getPlayer()->getPosition());

	//check if the game is over
	checkWin();
	checkDead();

	//update blood
	map->update(delta_seconds);

	// GUI
	health_indicator.update(delta_seconds);
	ammunition_indicator.update(delta_seconds);
	time_indicator.update(delta_seconds);
}

void GameState::checkWin()
{
	if (physics.isWin())
	{
		window->setMouseCursorVisible(true);
		done = true;
		State::nextState = std::make_shared<GameOverState>(window, true, time_indicator.getElapsedSeconds());
		if (isNotUserMap())
		{
			markMapAsCompleted();
		}
		std::cout << "win, time = " << time_indicator.getElapsedSeconds() << std::endl;
	}
}

bool GameState::isNotUserMap() const
{
	return map_index.has_value();
}

void GameState::markMapAsCompleted()
{
	std::ifstream ifstream("maps.bin", std::ios::binary);
	bool maps[18];
	for (int i = 0; i < 18; ++i)
	{
		char ch;
		ifstream >> ch;
		maps[i] = static_cast<bool>(ch);
	}
	ifstream.close();

	maps[map_index.value()] = true;

	std::ofstream ofstream("maps.bin", std::ios::binary | std::ios::trunc);
	for (int i = 0; i < 18; ++i)
	{
		ofstream << static_cast<char>(maps[i]);
	}
	ofstream.close();
}

void GameState::checkDead()
{
	if (physics.isDead())
	{
		window->setMouseCursorVisible(true);
		done = true;
		State::nextState = std::make_shared<GameOverState>(window, false);

		std::cout << "defeated, time = " << time_indicator.getElapsedSeconds() << std::endl;
	}
}

void GameState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear();
	window->setView(view);
	map->draw(window);

	window->setView(window->getDefaultView());
	window->draw(cursor);
	
	// GUI
	health_indicator.draw(window);
	ammunition_indicator.draw(window);
	time_indicator.draw(window);

	window->display();
};