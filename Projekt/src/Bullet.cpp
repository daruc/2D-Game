#include <iostream>

#include <box2d/box2d.h>
#include <box2d/b2_fixture.h>

#include "Bullet.h"
#include "Utils/Utils.h"
#include "FixtureId.h"

namespace
{
	const int SPEED = 20;
	const float SIZE = 0.04f;
}

Bullet::Bullet(b2World* b2world, sf::Vector2f source, sf::Vector2f direction)
	: ready_to_remove(false), b2world(b2world)
{
	//Creates physics object.
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.fixedRotation = true;
	body_def.bullet = true;

	body_def.position.Set(pixels2Meters(source.x), pixels2Meters(source.y));
	b2body = b2world->CreateBody(&body_def);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(SIZE / 2, SIZE / 2);

	b2FixtureDef fixture_def;
	fixture_def.shape = &dynamicBox;
	fixture_def.isSensor = true;
	fixture_def.userData.pointer = static_cast<uintptr_t>(FixtureId::BULLET);
	b2fixture = b2body->CreateFixture(&fixture_def);

	//Set velocity
	b2Vec2 velocity(direction.x, direction.y);

	velocity *= SPEED;

	std::cout << "v=(" << velocity.x << ", " << velocity.y << ")\n";
	b2body->SetLinearVelocity(velocity);

	float shape_size = meters2pixels(SIZE);
	shape.setSize(sf::Vector2f(shape_size, shape_size));
	shape.setPosition(pixels2Meters(source.x), pixels2Meters(source.y));
}

bool Bullet::isReadyToRemove() const
{
	return ready_to_remove;
}

void Bullet::update(float delta_seconds)
{
	b2Vec2 b2body_position = b2body->GetPosition();
	sf::Vector2f shape_position;
	shape_position.x = meters2pixels(b2body_position.x);
	shape_position.y = meters2pixels(b2body_position.y);
	shape.setPosition(shape_position);
}

void Bullet::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(shape);
}

void Bullet::beginContact(b2Contact* contact)
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

	if (fixtureHasId(other_fixture, FixtureId::ENEMY) ||
		fixtureHasId(other_fixture, FixtureId::FIRE) ||
		fixtureHasId(other_fixture, FixtureId::GROUND))
	{
		std::cout << "Bullet::beginContact\n";
		ready_to_remove = true;
	}
}

Bullet::~Bullet()
{
	std::cout << "Bullet::~Bullet()\n";
	b2world->DestroyBody(b2body);
}