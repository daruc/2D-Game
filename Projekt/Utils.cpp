#include "Utils.h"

float32 pixels2Meters(float pixels)
{
	return pixels / (float) FACTOR;
}

float meters2pixels(float32 meters)
{
	return meters * FACTOR;
}