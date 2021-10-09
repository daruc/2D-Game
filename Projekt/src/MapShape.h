#ifndef MAP_SHAPE_H
#define MAP_SHAPE_H

#include <SFML/Graphics.hpp>


class MapShape : public sf::ConvexShape
{
public:
	enum Type
	{
		GROUND, FIRE
	};
	inline void setType(Type type) { this->type = type; }
	inline Type getType() { return type; }

private:
	Type type;
};

#endif
