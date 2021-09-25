#include "Random.h"

float rand01()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float randAngleInDegrees()
{
	return rand01() * 360.0f;
}

int randRange(int min, int max)
{
	return (rand() % max) + min;
}