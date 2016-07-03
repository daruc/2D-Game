#include <iostream>
#include "MyContactListener.h"
#include "MapShape.h"

MyContactListener::MyContactListener()
{
	player = nullptr;
	finish = nullptr;
	touch_ground = false;
	on_ground = false;
	win = false;
	dead = false;
}


void MyContactListener::BeginContact(b2Contact* contact)
{
	//std::cout << "begin collision\n";
	
	touch_ground = true;

	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	if ((int)fixture_a->GetUserData() == 3
		|| (int) fixture_b->GetUserData() == 3)
	{
		std::cout << "begin sensor\n";
		on_ground = true;
	}

	bool bPlayer = false;
	bool bFinish = false;
	bool bFire = false;

	if (fixture_a == player || fixture_b == player)
	{
		bPlayer = true;
	}
	if (fixture_a == finish || fixture_b == finish)
	{
		bFinish = true;
	}
	if ((int)(fixture_a->GetUserData()) == MapShape::FIRE)
	{
		bFire = true;
	}

	if (bPlayer && bFinish)
	{
		std::cout << "game over\n";
		win = true;
	}

	if (bPlayer && bFire)
	{
		std::cout << "fire\n";
		dead = true;
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	//std::cout << "end collision\n";
	touch_ground = false;

	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	if ((int)fixture_a->GetUserData() == 3
		|| (int)fixture_b->GetUserData() == 3)
	{
		std::cout << "end sensor\n";
		on_ground = false;
	}
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}