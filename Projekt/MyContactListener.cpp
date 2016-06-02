#include <iostream>
#include "MyContactListener.h"

MyContactListener::MyContactListener()
{
	player = nullptr;
	finish = nullptr;
	on_ground = false;
	win = false;
}


void MyContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "begin collision\n";
	on_ground = true;

	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	bool bPlayer = false;
	bool bFinish = false;
	if (fixture_a == player || fixture_b == player)
	{
		bPlayer = true;
	}
	if (fixture_a == finish || fixture_b == finish)
	{
		bFinish = true;
	}

	if (bPlayer && bFinish)
	{
		std::cout << "game over\n";
		win = true;
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	std::cout << "end collision\n";
	on_ground = false;
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}