#include <iostream>
#include <box2d/box2d.h>
#include <box2d/b2_fixture.h>

#include "Utils/Utils.h"
#include "Enemy.h"
#include "SoundsSingleton.h"
#include "Map.h"
#include "FixtureId.h"


Enemy::Enemy()
	: sprite(6), b2world(nullptr), map(nullptr), b2fixture(nullptr), b2body(nullptr)
{
	if (!texture.loadFromFile("graphics/enemy.png"))
	{
		std::cout << "Can not load graphics/enemy.png";
	}

	sprite.loadTexture(texture);
	SoundsSingleton* sounds = SoundsSingleton::getInstance();
	sf::SoundBuffer* hit_sound_buffer = sounds->getHitEnemyBuffer();
	hit_sound.setBuffer(*hit_sound_buffer);
	int volume = sounds->getVolume();
	hit_sound.setVolume(volume);

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

void Enemy::initFixture(b2World* b2world, std::shared_ptr<Map> map)
{
	this->map = map;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	//sf::Vector2f position = getPosition();	// TODO

	//bodyDef.position.Set(pixels2Meters(position.x + 25), pixels2Meters(position.y + 50));
	b2body = b2world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f / 2, 2.0f / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 40.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.3f;
	fixtureDef.userData.pointer = static_cast<uintptr_t>(FixtureId::ENEMY);
	b2fixture = b2body->CreateFixture(&fixtureDef);

	assignSpritePositionToFixturePosition();
}

void Enemy::draw(std::shared_ptr<sf::RenderWindow> window)
{
	sprite.draw(window);
}

void Enemy::update(float delta_seconds)
{
	sprite.update(delta_seconds);

	if (b2body)
	{
		sf::Vector2f sprite_position;
		sprite_position.x = meters2pixels(b2body->GetPosition().x) - 25;
		sprite_position.y = meters2pixels(b2body->GetPosition().y) - 50;
		sprite.setPosition(sprite_position);
	}
}

void Enemy::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);

	if (b2body)
	{
		b2Vec2 fixture_position;
		fixture_position.x = pixels2Meters(pos.x + 25);
		fixture_position.y = pixels2Meters(pos.y + 50);
		b2body->SetTransform(fixture_position, 0.0f);
	}
}

void Enemy::assignSpritePositionToFixturePosition()
{
	sf::Vector2f sprite_position = sprite.getPosition();
	b2Vec2 fixture_position;
	fixture_position.x = pixels2Meters(sprite_position.x + 25);
	fixture_position.y = pixels2Meters(sprite_position.y + 50);
	b2body->SetTransform(fixture_position, 0.0f);
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

void Enemy::beginContact(b2Contact* contact)
{
	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	if (fixture_a != b2fixture && fixture_b != b2fixture)
	{
		return;
	}

	b2Fixture* other_fixture = fixture_a;
	if (fixture_a == b2fixture)
	{
		other_fixture = fixture_b;
	}

	if (fixtureHasId(other_fixture, FixtureId::BULLET))
	{
		b2Vec2 fixture_position = other_fixture->GetBody()->GetPosition();
		sf::Vector2f sprite_position;
		sprite_position.x = meters2pixels(fixture_position.x);
		sprite_position.y = meters2pixels(fixture_position.y);
		map->addBlood(sprite_position);
		hit_sound.play();
	}
}

Enemy::~Enemy()
{
	if (b2body)
	{
		b2world->DestroyBody(b2body);
	}
}