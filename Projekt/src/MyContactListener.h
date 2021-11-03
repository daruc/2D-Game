#ifndef MY_CONTACT_LISTENER_H
#define MY_CONTACT_LISTENER_H

#include <box2D/box2D.h>
#include <SFML/Audio.hpp>

#include "Map.h"


class MyContactListener : public b2ContactListener
{
private:
	bool touch_ground;
	bool on_ground;

	std::shared_ptr<Map> map;
	std::list<b2Body*>* remove_list;
	b2World* world_ptr;
	sf::Sound* ptr_knock;

public:
	MyContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	inline void setMap(std::shared_ptr<Map> map) { this->map = map; }
	inline void setKnockSound(sf::Sound* knock) { ptr_knock = knock; }
	inline void setRemoveList(std::list<b2Body*>* remove_list)
	{
		this->remove_list = remove_list;
	}
	inline void setWorld(b2World* world_ptr) { this->world_ptr = world_ptr; }
	inline bool touchGround() { return touch_ground; }
	inline bool isOnGround() { return on_ground; }
};

#endif