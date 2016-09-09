#include <iostream>
#include <cmath>
#include "Player.h"
#include "Utils.h"

const double pi = 3.14159265358979323846;

void Player::configureAnimations()
{
	sf::IntRect rect;
	rect.height = 100;
	rect.width = 50;

	rect.left = 0;
	rect.top = 0;

	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(RIGHT, rect);
		rect.left += rect.width;
	}
	rect.top = 100;
	rect.left = 450;
	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(LEFT, rect);
		rect.left -= rect.width;
	}

	sprite.setSpeed(12);
	sprite.setRepeated(RIGHT);
	sprite.setRepeated(LEFT);

	//test
	sprite.selectAnimation(LEFT);
}

Player::Player()
	: max_bullets(10), sprite(6)
{
	bullets = 10;
	health = 3;
	if (!texture_pistol.loadFromFile("graphics\\pistol.png"))
	{
		std::cout << "Cannot load pistol.png\n";
	}
	pistol.setTexture(texture_pistol);
	pistol.setOrigin(sf::Vector2f(5.0f, 5.0f));

	if (!texture.loadFromFile("graphics\\player.png"))
	{
		std::cout << "Cannot load player.png\n";
	}
	sprite.loadTexture(texture);
	float width = meters2pixels(1.0f);
	float height = meters2pixels(2.0f);
	sprite.setOrigin(sf::Vector2f(width / 2, height / 2));
	configureAnimations();
}

void Player::update(std::shared_ptr<sf::RenderWindow> window)
{
	sprite.update();

	//rotate gun
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2i center = sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2);
	int width = mouse.x - center.x;
	int height = mouse.y - center.y;

	double rad_angle = atan2(height, width);
	double deg_angle = rad_angle * 180 / pi;

	pistol.setRotation(deg_angle);

	if (mouse.x < center.x)
	{
		sf::Vector2u size = texture_pistol.getSize();
		sf::IntRect rect = sf::IntRect(0, size.y, size.x, -size.y);
		pistol.setTextureRect(rect);
		pistol.setOrigin(sf::Vector2f(5.0f, 16.0f));
	}
	else
	{
		sf::Vector2u size = texture_pistol.getSize();
		sf::IntRect rect = sf::IntRect(0, 0, size.x, size.y);
		pistol.setTextureRect(rect);
		pistol.setOrigin(sf::Vector2f(5.0f, 5.0f));
	}

	sf::Vector2f origin = pistol.getOrigin();
}

void Player::draw(std::shared_ptr<sf::RenderWindow> window)
{
	sprite.draw(window);
	window->draw(pistol);
}

void Player::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
	sf::Vector2f pistol_pos = pos;
	pistol_pos.x += meters2pixels(0.04f);
	pistol_pos.y += meters2pixels(-0.08f);
	pistol.setPosition(pistol_pos);
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

void Player::goLeft()
{
	sprite.selectAnimation(LEFT);
	if (sprite.getDirection(LEFT) == false)
	{
		sprite.setDirection(LEFT, true);
	}
	sprite.stopAnimation(false);
}

void Player::goRight()
{
	sprite.selectAnimation(RIGHT);
	if (sprite.getDirection(RIGHT) == false)
	{
		sprite.setDirection(RIGHT, true);
	}
	sprite.stopAnimation(false);
}

void Player::stopLeft()
{
	sprite.selectAnimation(LEFT);
	sprite.setDirection(LEFT, true);
	sprite.stopAnimation(true);
}

void Player::stopRight()
{
	sprite.selectAnimation(RIGHT);
	sprite.setDirection(RIGHT, true);
	sprite.stopAnimation(true);
}

void Player::goLeftBack()
{
	sprite.selectAnimation(RIGHT);
	if (sprite.getDirection(RIGHT))
	{
		sprite.setDirection(RIGHT, false);
	}
	
	sprite.stopAnimation(false);
}

void Player::goRightBack()
{
	sprite.selectAnimation(LEFT);
	if (sprite.getDirection(LEFT))
	{
		sprite.setDirection(LEFT, false);
	}
	sprite.stopAnimation(false);
}

bool Player::shoot()
{
	if (bullets > 0)
	{
		--bullets;
		return true;
	}

	return false;
}

bool Player::reload()
{
	if (bullets == 0)
	{
		bullets = max_bullets;
		return true;
	}

	return false;
}