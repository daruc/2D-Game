#include "Enemy.h"
#include <iostream>


Enemy::Enemy()
	: sprite(6)
{
	if (!texture.loadFromFile("graphics/enemy.png"))
	{
		std::cout << "Can not load graphics/enemy.png";
	}

	sprite.loadTexture(texture);
	configureAnimation();
	update(0);
}

void Enemy::configureAnimation()
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

	rect.height = 50;
	rect.left = 0;
	rect.top = 200;
	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(CROUCH_RIGHT, rect);
		rect.left += rect.width;
	}
	rect.top = 250;
	rect.left = 450;
	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(CROUCH_LEFT, rect);
		rect.left -= rect.width;
	}

	sprite.setSpeed(12);
	sprite.setRepeated(RIGHT);
	sprite.setRepeated(LEFT);
	sprite.setRepeated(CROUCH_RIGHT);
	sprite.setRepeated(CROUCH_LEFT);

	sprite.selectAnimation(LEFT);
}

void Enemy::draw(std::shared_ptr<sf::RenderWindow> window)
{
	sprite.draw(window);
}

void Enemy::update(float delta_seconds)
{
	sprite.update(delta_seconds);
}

void Enemy::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

sf::Vector2f Enemy::getPosition() const
{
	return sprite.getPosition();
}

std::vector<char> Enemy::toBinary() const
{
	sf::Vector2f position = getPosition();
	size_t size = sizeof(position);
	std::vector<char> buffer(size);
	memcpy(buffer.data(), &position, size);

	return buffer;
}

void Enemy::fromBinary(char* bytes)
{
	sf::Vector2f position;
	memcpy(&position, bytes, sizeof(position));
	setPosition(position);
}

size_t Enemy::binarySize() const
{
	return sizeof(getPosition());
}