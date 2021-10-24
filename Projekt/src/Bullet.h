#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "Updatable.h"
#include "Fixture.h"

class b2Body;
class b2World;
class b2Fixture;

class Bullet : public Updatable, public Drawable, public Fixture
{
private:
	bool ready_to_remove;
	b2World* b2world;
	sf::RectangleShape shape;
	b2Body* b2body;
	b2Fixture* b2fixture;

public:
	Bullet(b2World* b2world, sf::Vector2f source, sf::Vector2f direction);
	~Bullet();
	bool isReadyToRemove() const;
	void beginContact(b2Contact* contact) override;
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
};

#endif