#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <cmath>


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