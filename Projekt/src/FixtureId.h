#ifndef FIXTURE_ID_H
#define FIXTURE_ID_H

#include <box2d/box2d.h>

enum class FixtureId : uintptr_t
{
	PLAYER,
	FINISH,
	GROUND,
	FIRE,
	ENEMY,
	BULLET
};

bool fixtureHasId(b2Fixture* fixture, FixtureId id);

#endif