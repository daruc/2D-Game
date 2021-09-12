#include <iostream>
#include <sstream>
#include <thread>
#include "GameState.h"
#include "MapMenuState.h"
#include "GameOverState.h"
#include "Utils.h"
#include "Enemy.h"


GameState::GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Map> map)
	: State(window), physics(window, map, player, enemies)
{
	done = false;
	this->map = map;
	textures.loadCursor();
	textures.loadClock();
	textures.loadHealth();
	textures.loadGunGui();
	textures.loadFinish();
	textures.loadMapType(map->getType());
	map->setGroundTexture(textures.getGround());
	cursor.setTexture(*textures.getCursor(), true);
	sprite_clock.setTexture(*textures.getClock(), true);
	sprite_gun.setTexture(*textures.getGunGui(), true);
	
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

	player.setPosition(map->getPlayerPosition());
	health.setPosition(0.0f, 0.0f);
	int h = player.getHealth();
	health.setTexture(*textures.getHealth(h));

	// enemies
	auto enemiesBegin = map->getEnemiesBegin();
	auto enemiesEnd = map->getEnemiesEnd();

	for (auto enemyIt = enemiesBegin; enemyIt != enemiesEnd; ++enemyIt)
	{
		auto enemy = std::make_shared<Enemy>();
		enemy->setPosition((*enemyIt)->getPosition());
		enemies.push_back(enemy);
	}

	finish.setPosition(map->getFinishPosition());
	finish.setTexture(*textures.getFinish(), true);
	int width = meters2pixels(1.0f);
	int height = meters2pixels(1.0f);
	finish.setOrigin(sf::Vector2f(width / 2, height / 2));

	view.setSize(window->getSize().x, window->getSize().y);
	view.move(player.getPosition() - view.getCenter());

	if (!gunshot_buffer.loadFromFile("sounds\\gunshot.wav"))
	{
		std::cout << "Cannot load file gunshot.wav\n";
	}
	gunshot.setBuffer(gunshot_buffer);

	if (!hit_enemy_buffer.loadFromFile("sounds\\hit_enemy.wav"))
	{
		std::cout << "Cannot load file hit_enemy.wav\n";
	}
	hit_enemy.setBuffer(hit_enemy_buffer);
	physics.setHitEnemySound(&hit_enemy);

	if (!knock_buffer.loadFromFile("sounds\\knock.wav"))
	{
		std::cout << "Cannot load file knock.wav\n";
	}
	knock.setBuffer(knock_buffer);
	knock.setVolume(50);
	physics.setKnockSound(&knock);


	if (!empty_gun_buffer.loadFromFile("sounds\\empty_gun.wav"))
	{
		std::cout << "Cannnot load file emtpy_gun.wav\n";
	}
	empty_gun.setBuffer(empty_gun_buffer);
	empty_gun.setVolume(50);

	if (!reload_buffer.loadFromFile("sounds\\reload.wav"))
	{
		std::cout << "Cannot load file reload.wav\n";
	}
	reload.setBuffer(reload_buffer);

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

GameState::~GameState()
{

}

void GameState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			done = true;
			gui_thread->join();
			window->close();
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->setMouseCursorVisible(true);
				done = true;
				gui_thread->join();
				State::nextState = std::make_shared<MapMenuState>(window);
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				std::cout << "click fire\n";
				if (player.shoot())
				{
					int blts = player.getBullets();
					std::stringstream stream;
					stream << blts;
					bullets.setString(stream.str());
					gunshot.play();
					sf::Vector2f mouse = cursor.getPosition();
					sf::Vector2f playerPosition = player.getPosition();
					sf::Vector2u resolution = window->getSize();

					physics.throwBullet(playerPosition.x, playerPosition.y,
						mouse.x - resolution.x / 2, mouse.y - resolution.y / 2);
				}
				else
				{
					empty_gun.play();
				}
			}
			if (event.key.code == sf::Mouse::Right)
			{
				std::cout << "click reload\n";
				if (player.reload())
				{
					int blts = player.getBullets();
					std::stringstream stream;
					stream << blts;
					bullets.setString(stream.str());
					reload.play();
				}
			}
		}
	}
}
void GameState::update()
{
	//update cursor position
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	cursor.setPosition(sf::Vector2f(mouse.x, mouse.y));

	//calculate physics
	physics.simulate();

	//player's sprite
	
	player.update(window);
	player.setPosition(map->getPlayerPosition());

	// enemies

	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		enemy->update();
	}

	//set camera
	view.setCenter(player.getPosition());

	//check if the game is over
	if (physics.isWin())
	{
		window->setMouseCursorVisible(true);
		done = true;
		gui_thread->join();
		State::nextState = std::make_shared<GameOverState>(window, true, clock.getElapsedTime().asSeconds());

		std::cout << "win, time = " << clock.getElapsedTime().asSeconds() << std::endl;
	}
	if (physics.isDead())
	{
		window->setMouseCursorVisible(true);
		done = true;
		gui_thread->join();
		State::nextState = std::make_shared<GameOverState>(window, false);

		std::cout << "defeated, time = " << clock.getElapsedTime().asSeconds() << std::endl;
	}

	//update blood
	map->updateBlood();

}
void GameState::draw()
{
	window->clear();
	window->setView(view);
	map->draw(*window);
	player.draw(window);

	// enemies
	for (std::shared_ptr<Enemy> enemy : enemies)
	{
		enemy->draw(window);
	}

	window->draw(finish);
	window->setView(window->getDefaultView());
	window->draw(cursor);
	mtx.lock();
	window->draw(txtTime);
	mtx.unlock();
	window->draw(bullets);
	window->draw(sprite_clock);
	window->draw(sprite_gun);
	window->draw(health);
	window->display();
};