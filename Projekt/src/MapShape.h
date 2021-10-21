#ifndef MAP_SHAPE_H
#define MAP_SHAPE_H

#include <SFML/Graphics.hpp>
#include "Binary.h"


class MapShape : public sf::ConvexShape, public Binary
{
public:
	enum Type
	{
		GROUND, FIRE
	};
	void setType(Type type);
	Type getType() const;

	std::vector<char> toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;

private:
	Type type;
};

#endif
