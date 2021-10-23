#ifndef TIME_INDICATOR_H
#define TIME_INDICATOR_H

#include <SFML/Graphics.hpp>

#include "../Drawable.h"
#include "../Updatable.h"


class TimeIndicator	: public Drawable, public Updatable
{
private:
	float elapsed_seconds;
	sf::Sprite sprite;
	sf::Text text;

public:
	TimeIndicator(std::shared_ptr<sf::RenderWindow> window);
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	float getElapsedSeconds() const;
};

#endif // !TIME_INDICATOR_H
