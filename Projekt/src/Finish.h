#ifndef FINISH_H
#define FINISH_H

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "Binary.h"
#include "Fixture.h"


class b2Body;
class b2World;
class Map;

class Finish : public Drawable, public Binary, public Fixture
{
private:
	sf::Sprite sprite;
	b2Body* b2body;
	b2World* b2world;

public:
	Finish();
	~Finish();
	void initFixture(b2World* b2world, std::shared_ptr<Map> map);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;

	std::vector<char> toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;
};

#endif