#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "Control.h"


class TextField : public Control
{
private:
	sf::RectangleShape rectangle;
	sf::RectangleShape cursor;
	sf::Text text;
	sf::String real_text;
	sf::String printed_text;
	sf::Font font;
	bool focus;
	bool visible_cursor;
	sf::Clock cursor_clock;
	void handleKeys(sf::Event & event);

public:
	TextField(std::shared_ptr<sf::RenderWindow> window);
	virtual void handleEvents(sf::Event & event);
	void update() override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	inline sf::String getString() { return text.getString(); }

	void setDimensions(float width, float height);
	void setCoordinates(float x, float y);
};

#endif