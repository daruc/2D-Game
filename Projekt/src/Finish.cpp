#include "Finish.h"
#include "Utils/Utils.h"
#include "TexturesSingleton.h"


Finish::Finish()
{
	TexturesSingleton* textures = TexturesSingleton::getInstance();
	textures->loadFinish();

	sprite.setTexture(*textures->getFinish(), true);
	int width = meters2pixels(1.0f);
	int height = meters2pixels(1.0f);
	sprite.setOrigin(sf::Vector2f(width, height) / 2.0f);
}

void Finish::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

void Finish::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

sf::Vector2f Finish::getPosition() const
{
	return sprite.getPosition();
}

std::vector<char> Finish::toBinary() const
{
	sf::Vector2f position = getPosition();
	size_t size = sizeof(position);
	std::vector<char> buffer(size);
	memcpy(buffer.data(), &position, size);

	return buffer;
}

void Finish::fromBinary(char* bytes)
{
	sf::Vector2f position;
	memcpy(&position, bytes, sizeof(position));
	setPosition(position);
}

size_t Finish::binarySize() const
{
	return sizeof(getPosition());
}