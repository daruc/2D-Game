#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <SFML/Audio.hpp>
#include <optional>
#include "AnimatedSprite.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Binary.h"
#include "Fixture.h"


class b2Body;
class b2Fixture;
class b2World;
class Map;

class Enemy : public Updatable, public Drawable, public Binary, public Fixture
{
private:
	enum Anim {
		RIGHT = 0, LEFT = 1, CROUCH_RIGHT = 2, CROUCH_LEFT = 3
	};

	sf::Texture texture;
	AnimatedSprite sprite;
	sf::Sound hit_sound;

	b2World* b2world;
	b2Fixture* b2fixture;
	b2Body* b2body;
	std::shared_ptr<Map> map;

	void configureAnimation();
	void createFixture();
	void assignSpritePositionToFixturePosition();

public:
	Enemy();
	~Enemy();
	void initFixture(b2World* b2world, std::shared_ptr<Map> map);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float delta_seconds) override;
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const;

	std::vector<char> toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;

	void beginContact(b2Contact* contact) override;
};

#endif
