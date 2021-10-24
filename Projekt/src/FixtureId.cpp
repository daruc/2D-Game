#include "FixtureId.h"

bool fixtureHasId(b2Fixture* fixture, FixtureId id)
{
	return fixture->GetUserData().pointer == static_cast<uintptr_t>(id);
}