#ifndef MAP_SHAPE_H
#define MAP_SHAPE_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Binary.h"
#include "Fixture.h"


class b2Body;
class b2World;

class MapShape : public sf::ConvexShape, public Binary, public Fixture
{
public:
	enum Type
	{
		GROUND, FIRE
	};

	MapShape();
	~MapShape();
	void initFixture(b2World* b2world);
	std::vector<b2Vec2> getPoints();

	void setType(Type type);
	Type getType() const;

	std::vector<char> toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;

private:
	Type type;
	b2Body* b2body;
	b2World* b2world;
};

#endif
