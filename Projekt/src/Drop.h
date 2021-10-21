#ifndef DROP_H
#define DROP_H

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "Updatable.h"


class Drop : public Drawable, public Updatable
{
private:
	const float SHOW_TIME = 0.8f;
	const float GRAVITATION = 5.0f;
	const float SPEED = 0.003f;
	const sf::Color COLOR;
	const sf::Uint8 MAX_OPACITY = 255;
	const int MAX_SIZE = 6;
	const int MIN_SIZE = 1;
	
	float secondsToDestroy;
	sf::Vector2f velocity;
	sf::RectangleShape shape;

	sf::Vector2f getRandomSize() const;
	sf::Vector2f getRandomVelocity() const;
	void updateSecondsToDestroy(float delta_seconds);
	void updateGravitation(float delta_seconds);
	void updateTransparency();

public:
	Drop(sf::Vector2f position);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float delta_seconds) override;
	bool isReadyToDestroy();
};

#endif // !DROP_H

