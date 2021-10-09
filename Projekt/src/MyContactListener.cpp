#include <iostream>
#include "MyContactListener.h"
#include "MapShape.h"
#include "Utils/Utils.h"


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
	touch_ground = true;

	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	if (reinterpret_cast<int&>(fixture_a->GetUserData()) == 3
		|| reinterpret_cast<int&>(fixture_b->GetUserData()) == 3)
	{
		std::cout << "begin sensor\n";
		on_ground = true;
	}

	if (reinterpret_cast<int&>(fixture_a->GetUserData()) == 10 && fixture_b != player
		&& reinterpret_cast<int&>(fixture_b->GetUserData()) != 3)
	{
		auto it_1 = bullet_list->begin();
		auto it_2 = map->getBulletsList()->begin();

		bool found = false;
		do 
		{
			auto fixture_from_list = (*it_1)->GetFixtureList();
			if (fixture_from_list == fixture_a)
			{

				std::cout << "found bullet\n";
				found = true;
			}
			if (!found)
			{
				++it_1;
				++it_2;
			}
		} while (!found);

		remove_list->push_back(*it_1);
		bullet_list->erase(it_1);
		map->getBulletsList()->erase(it_2);
	}

	if (reinterpret_cast<int&>(fixture_b->GetUserData()) == 10 && fixture_a != player
		&& reinterpret_cast<int&>(fixture_a->GetUserData()) != 3)
	{
		auto it_1 = bullet_list->begin();
		auto it_2 = map->getBulletsList()->begin();

		bool found = false;
		do
		{
			auto fixture_from_list = (*it_1)->GetFixtureList();
			if (fixture_from_list == fixture_b)
			{
				b2Vec2 position = fixture_b->GetBody()->GetPosition();

				if (reinterpret_cast<int&>(fixture_a->GetUserData()) == 20)
				{
					float bloodPositionX = meters2pixels(position.x);
					float bloodPositionY = meters2pixels(position.y);
					sf::Vector2f bloodPosition(bloodPositionX, bloodPositionY);
					map->addBlood(bloodPosition);
					ptr_hit_enemy->play();
				}
				
				std::cout << "found bullet\n";
				found = true;
			}
			if (!found)
			{
				++it_1;
				++it_2;
			}
		} while (!found);

		remove_list->push_back(*it_1);
		bullet_list->erase(it_1);
		map->getBulletsList()->erase(it_2);
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
	if (reinterpret_cast<int&>(fixture_a->GetUserData()) == MapShape::FIRE)
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

	if (bPlayer)
	{
		std::cout << "play knock\n";
		ptr_knock->play();
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	touch_ground = false;

	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	if (reinterpret_cast<int&>(fixture_a->GetUserData()) == 3
		|| reinterpret_cast<int&>(fixture_b->GetUserData()) == 3)
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