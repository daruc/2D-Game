#ifndef MY_CONTACT_LISTENER_H
#define MY_CONTACT_LISTENER_H
#include <Box2D/Box2D.h>

class MyContactListener : public b2ContactListener
{
private:
	bool on_ground;
	b2Fixture* player;
	b2Fixture* finish;
	bool win;
public:
	MyContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	inline bool isOnGround() { return on_ground; }
	inline void setPlayerFixture(b2Fixture* player) { this->player = player; }
	inline void setFinishFixture(b2Fixture* finish) { this->finish = finish; }
	inline bool isWin() const { return win; }
};

#endif