#ifndef FINISH_H
#define FINISH_H

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "Textures.h"
#include "Binary.h"


class Finish : public Drawable, public Binary
{
private:
	Textures textures;
	sf::Sprite sprite;

public:
	Finish();
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;

	std::vector<char> toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;
};

#endif