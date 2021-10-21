#include "MapShape.h"


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