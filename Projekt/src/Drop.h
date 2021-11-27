#ifndef DROP_H
#define DROP_H

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "Updatable.h"


class Drop : public Drawable, public Updatable
{
private:
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

