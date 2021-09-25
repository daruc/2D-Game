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

	void setTextPosition();

public:
	Button(std::shared_ptr<sf::RenderWindow> window, std::string title);
	Button(std::shared_ptr<sf::RenderWindow> window, std::wstring title);
	virtual void handleEvents(sf::Event & event);
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setDimensions(float width, float height);
	void setCoordinates(float x, float y);
};

#endif