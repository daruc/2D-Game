#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace
{
	const float PI = 3.14159;
}

float pixels2Meters(float pixels)
{
	return pixels / (float) FACTOR;
}

float meters2pixels(float meters)
{
	return meters * FACTOR;
}

void normalizeVector(sf::Vector2f* vectorPtr)
{
	float x = vectorPtr->x;
	float y = vectorPtr->y;

	float length = sqrt((x * x) + (y * y));
	*vectorPtr /= length;
}

sf::Vector2f rectDimensions(sf::FloatRect rect)
{
	return sf::Vector2f(rect.width, rect.height);
}

float rad2Deg(float rad)
{
	return rad * 180 / PI;
}