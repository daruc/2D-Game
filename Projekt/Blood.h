#ifndef BLOOD_H_
#define BLOOD_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include "Drawable.h"
#include "Updatable.h"


namespace sf
{
	class sf::RenderWindow;
}

class Drop;

const std::size_t DROPS = 50;
const float SHOW_TIME = 0.8;

class Blood : public Drawable, public Updatable
{
private:
	std::vector<std::shared_ptr<Drop>> drops;

public:
	Blood(sf::Vector2f position);
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	bool isReadyToDestroy() const;
};

#endif