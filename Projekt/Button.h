#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "Control.h"

class Button : public Control
{
protected:
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::Font font;
	bool click;
public:
	Button(std::shared_ptr<sf::RenderWindow> window, std::string title);
	virtual void update();
	virtual void draw();

	void setDimensions(float width, float height);
	void setCoordinates(float x, float y);
};

#endif