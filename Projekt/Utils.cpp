#include "Utils.h"


float pixels2Meters(float pixels)
{
	return pixels / (float) FACTOR;
}

float meters2pixels(float meters)
{
	return meters * FACTOR;
}