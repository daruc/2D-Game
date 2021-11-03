#include <vector>
#include <box2d/box2d.h>
#include "MapShape.h"
#include "Utils/Utils.h"
#include "FixtureId.h"


MapShape::MapShape()
	: b2body(nullptr),
	b2world(nullptr)
{

}

MapShape::~MapShape()
{
	if (b2body)
	{
		b2world->DestroyBody(b2body);
	}
}

void MapShape::initFixture(b2World* b2world)
{
	b2BodyDef ground_body_def;
	ground_body_def.position.Set(pixels2Meters(getPosition().x), pixels2Meters(getPosition().y));
	b2body = b2world->CreateBody(&ground_body_def);
	b2PolygonShape ground_box;
	std::vector<b2Vec2> points = getPoints();
	ground_box.Set(points.data(), points.size());

	b2FixtureDef fixture_def = {};
	fixture_def.shape = &ground_box;
	fixture_def.userData.pointer = static_cast<uintptr_t>(FixtureId::GROUND);

	b2body->CreateFixture(&fixture_def);
}

std::vector<b2Vec2> MapShape::getPoints()
{
	size_t size = getPointCount();
	std::vector<b2Vec2> points(size);

	for (size_t i = 0; i < size; ++i)
	{
		sf::Vector2f point = getPoint(i);
		points[i] = b2Vec2(pixels2Meters(point.x), pixels2Meters(point.y));
	}

	return points;
}

void MapShape::setType(Type type)
{
	this->type = type;
}

MapShape::Type MapShape::getType() const
{
	return type;
}

std::vector<char> MapShape::toBinary() const
{
	int type_int = static_cast<int>(type);
	size_t point_count = getPointCount();
	sf::Vector2f position = getPosition();

	std::vector<char> bytes(binarySize());
	char* ptr = bytes.data();

	memcpy(ptr, &type_int, sizeof(type_int));
	ptr += sizeof(type_int);
	memcpy(ptr, &point_count, sizeof(point_count));
	ptr += sizeof(getPointCount());
	memcpy(ptr, &position, sizeof(position));
	ptr += sizeof(position);

	for (size_t i = 0; i < point_count; ++i)
	{
		sf::Vector2f point = getPoint(i);
		memcpy(ptr, &point, sizeof(point));
		ptr += sizeof(point);
	}

	return bytes;
}

void MapShape::fromBinary(char* bytes)
{
	char* ptr = bytes;

	int int_type;
	memcpy(&int_type, ptr, sizeof(int_type));
	ptr += sizeof(int_type);

	size_t verticles;
	memcpy(&verticles, ptr, sizeof(verticles));
	ptr += sizeof(verticles);

	sf::Vector2f position;
	memcpy(&position, ptr, sizeof(position));
	ptr += sizeof(position);

	setPosition(position);
	setPointCount(verticles);	//error here
	setType((MapShape::Type)int_type);

	for (size_t i = 0; i < verticles; ++i)
	{
		sf::Vector2f point;
		memcpy(&point, ptr, sizeof(point));
		ptr += sizeof(point);
		setPoint(i, point);
	}
}

size_t MapShape::binarySize() const
{
	return sizeof(getPointCount()) + sizeof(int) + sizeof(getPosition())
		+ getPointCount() * sizeof(sf::Vector2f);
}