#ifndef MY_CONTACT_LISTENER_H
#define MY_CONTACT_LISTENER_H
#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>
#include "Map.h"

class MyContactListener : public b2ContactListener
{
private:
	bool touch_ground;
	bool on_ground;
	b2Fixture* player;
	b2Fixture* finish;
	bool win;
	bool dead;

	std::shared_ptr<Map> map;
	std::list<b2Body*>* bullet_list;
	std::list<b2Body*>* remove_list;
	b2World* world_ptr;
	sf::Sound* ptr_hit_enemy;
	sf::Sound* ptr_knock;
public:
	MyContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	inline void setMap(std::shared_ptr<Map> map) { this->map = map; }
	inline void setHitEnemySound(sf::Sound* hit_enemy) { ptr_hit_enemy = hit_enemy; }
	inline void setKnockSound(sf::Sound* knock) { ptr_knock = knock; }
	inline void setBulletList(std::list<b2Body*>* bullet_list)
	{
		this->bullet_list = bullet_list;
	}
	inline void setRemoveList(std::list<b2Body*>* remove_list)
	{
		this->remove_list = remove_list;
	}
	inline void setWorld(b2World* world_ptr) { this->world_ptr = world_ptr; }
	inline bool touchGround() { return touch_ground; }
	inline bool isOnGround() { return on_ground; }
	inline void setPlayerFixture(b2Fixture* player) { this->player = player; }
	inline void setFinishFixture(b2Fixture* finish) { this->finish = finish; }
	inline bool isWin() const { return win; }
	inline bool isDead() const { return dead; }
};

#endif