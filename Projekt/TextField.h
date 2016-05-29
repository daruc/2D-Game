#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H
#include "Control.h"

class TextField : public Control
{
private:
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::Font font;
	bool focus;
	void handleKeys(sf::Event & event);
public:
	TextField(std::shared_ptr <sf::RenderWindow> window);
	virtual void handleEvents(sf::Event & event);
	virtual void update();
	virtual void draw();
	inline sf::String getString() { return text.getString(); }

	void setDimensions(float width, float height);
	void setCoordinates(float x, float y);
};

#endif