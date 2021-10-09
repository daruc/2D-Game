#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "Control.h"


class ButtonState;

class Button : public Control
{
protected:
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::Font font;

	void loadFont();
	void initButton(sf::String title);
	void initText(sf::String title);
	void initBackground();
	void setTextPosition();
	bool isMouseButtonReleasedInsideButton(sf::Event & event);
	bool isMouseButtonReleased(sf::Event & event);
	bool isMouseInsideButton();
	bool isLeftMouseButtonPressed();
	void setPressed();
	void setFocused();
	void setIdle();

public:
	Button(std::shared_ptr<sf::RenderWindow> window, std::string title);
	Button(std::shared_ptr<sf::RenderWindow> window, std::wstring title);
	void handleEvents(sf::Event & event) override;
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setDimensions(float width, float height);
	void setDimensions(sf::Vector2f dimensions);
	void setCoordinates(float x, float y);
};

#endif