#include "Finish.h"
#include "Utils/Utils.h"
#include "TexturesSingleton.h"
#include "FixtureId.h"
#include "Map.h"


Finish::Finish()
{
	TexturesSingleton* textures = TexturesSingleton::getInstance();
	textures->loadFinish();

	sprite.setTexture(*textures->getFinish(), true);
	int width = meters2pixels(1.0f);
	int height = meters2pixels(1.0f);
	sprite.setOrigin(sf::Vector2f(width, height) / 2.0f);
}

Finish::~Finish()
{
	if (b2body)
	{
		b2world->DestroyBody(b2body);
	}
}

void Finish::initFixture(b2World* b2world, std::shared_ptr<Map> map)
{
	this->b2world = b2world;

	b2BodyDef finishBodyDef;
	sf::Vector2f finish_position = map->getFinishPosition();
	finishBodyDef.position.Set(pixels2Meters(finish_position.x), pixels2Meters(finish_position.y));
	b2body = b2world->CreateBody(&finishBodyDef);
	b2PolygonShape finishBox;
	finishBox.SetAsBox(1.0f / 2, 1.0f / 2);

	b2FixtureDef finishSensorFixtureDef;
	finishSensorFixtureDef.shape = &finishBox;
	finishSensorFixtureDef.isSensor = true;
	finishSensorFixtureDef.userData.pointer = static_cast<uintptr_t>(FixtureId::FINISH);
	b2body->CreateFixture(&finishSensorFixtureDef);
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