#ifndef UTILS_H
#define UTILS_H

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>


#define FACTOR 50

float pixels2Meters(float pixels);
float meters2pixels(float meters);
void normalizeVector(sf::Vector2f* vectorPtr);
sf::Vector2f rectDimensions(sf::FloatRect rect);
float rad2Deg(float rad);

#endif