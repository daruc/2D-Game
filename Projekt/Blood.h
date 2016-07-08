#ifndef BLOOD_H_
#define BLOOD_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#define DROPS 50
#define SHOW_TIME 0.8

class Blood
{
private:
	sf::Clock clock;
	std::shared_ptr<sf::RectangleShape> drop[DROPS];
	sf::Vector2f vector[DROPS];
	bool out_of_date;
	sf::Time lastUpdateTime;
public:
	Blood(float x, float y);
	void update();
	void draw(sf::RenderWindow & window);
	inline bool isOutOfDate() { return out_of_date; }
};

#endif