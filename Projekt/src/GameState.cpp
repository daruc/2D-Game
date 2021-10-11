#include <iostream>
#include <sstream>
#include <thread>

#include "GameState.h"
#include "MapMenuState.h"
#include "GameOverState.h"
#include "Utils/Utils.h"
#include "Enemy.h"


GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window), physics(window, map), health_picture(map->getPlayer())
{
	done = false;
	this->map = map;
	loadTextures();
	
	cursor.setOrigin(16.0f, 16.0f);
	cursor.setPosition(.0f, 0.0f);

	font.loadFromFile("font.ttf");
	txtTime.setFont(font);
	txtTime.setString("0");
	sf::Vector2u resolution = State::window->getSize();
	txtTime.setCharacterSize(17.0f);
	txtTime.setPosition(resolution.x / 2, 8.0f);
	sf::Vector2f clock_pos = txtTime.getPosition();
	clock_pos.x -= 37.0f;
	clock_pos.y -= 8.0f;
	sprite_clock.setPosition(clock_pos);

	bullets.setFont(font);
	bullets.setString("10");
	bullets.setPosition(resolution.x - 70, 8.0f);
	bullets.setCharacterSize(17);

	window->setMouseCursorVisible(false);

	view.setSize(window->getSize().x, window->getSize().y);
	view.move(map->getPlayer()->getPosition() - view.getCenter());

	loadSounds();

	sprite_gun.setPosition(resolution.x - sprite_gun.getLocalBounds().width, 8.0f);

	clock.restart();

	gui_thread = std::make_shared<std::thread>([this]() {
		while (!done)
		{
			float seconds = clock.getElapsedTime().asMilliseconds() / 1000.0;
			std::stringstream stream;
			stream.precision(1);
			stream << std::fixed << seconds;
			mtx.lock();
			txtTime.setString(stream.str());
			mtx.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	});
}

void GameState::loadTextures()
{
	textures.loadCursor();
	textures.loadClock();
	textures.loadGunGui();
	textures.loadFinish();
	textures.loadMapType(map->getType());
	map->setGroundTexture(textures.getGround());
	cursor.setTexture(*textures.getCursor(), true);
	sprite_clock.setTexture(*textures.getClock(), true);
	sprite_gun.setTexture(*textures.getGunGui(), true);
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
	gui_thread->join();
	window->close();
}

void GameState::handleEventExitToMenu()
{
	window->setMouseCursorVisible(true);
	done = true;
	gui_thread->join();
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
	int blts = map->getPlayer()->getBullets();
	std::stringstream stream;
	stream << blts;
	bullets.setString(stream.str());
	gunshot.play();
	sf::Vector2f mouse = cursor.getPosition();
	sf::Vector2f playerPosition = map->getPlayer()->getPosition();
	sf::Vector2u resolution = window->getSize();

	physics.throwBullet(playerPosition.x, playerPosition.y,
		mouse.x - resolution.x / 2, mouse.y - resolution.y / 2);
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
		int blts = map->getPlayer()->getBullets();
		std::stringstream stream;
		stream << blts;
		bullets.setString(stream.str());
		reload.play();
	}
}

void GameState::update(float deltaSeconds)
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
	map->update(deltaSeconds);

	// GUI
	health_picture.update(deltaSeconds);
}

void GameState::checkWin()
{
	if (physics.isWin())
	{
		window->setMouseCursorVisible(true);
		done = true;
		gui_thread->join();
		State::nextState = std::make_shared<GameOverState>(window, true, clock.getElapsedTime().asSeconds());

		std::cout << "win, time = " << clock.getElapsedTime().asSeconds() << std::endl;
	}
}

void GameState::checkDead()
{
	if (physics.isDead())
	{
		window->setMouseCursorVisible(true);
		done = true;
		gui_thread->join();
		State::nextState = std::make_shared<GameOverState>(window, false);

		std::cout << "defeated, time = " << clock.getElapsedTime().asSeconds() << std::endl;
	}
}

void GameState::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear();
	window->setView(view);
	map->draw(window);

	window->setView(window->getDefaultView());
	window->draw(cursor);
	mtx.lock();
	window->draw(txtTime);
	mtx.unlock();
	window->draw(bullets);
	window->draw(sprite_clock);
	window->draw(sprite_gun);
	health_picture.draw(window);
	window->display();
};