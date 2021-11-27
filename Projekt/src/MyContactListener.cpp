#include <iostream>
#include "MyContactListener.h"
#include "MapShape.h"
#include "Utils/Utils.h"
#include "Bullet.h"
#include "Enemy.h"


MyContactListener::MyContactListener()
{
	touch_ground = false;
	on_ground = false;
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	touch_ground = true;

	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();


	for (std::shared_ptr<Bullet> bullet : *map->getBulletsList())
	{
		bullet->beginContact(contact);
	}

	for (std::shared_ptr<Enemy> enemy : *map->getEnenemiesList())
	{
		enemy->beginContact(contact);
	}

	map->getPlayer()->beginContact(contact);
}

void MyContactListener::EndContact(b2Contact* contact)
{
	touch_ground = false;

	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	map->getPlayer()->endContact(contact);
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}