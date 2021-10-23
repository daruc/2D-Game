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
	bool focus;
	bool visible_cursor;
	float seconds_to_change_cursor_visibility;

	void initText();
	void initRectangle();
	void initCursor();
	bool isMouseButtonReleased(sf::Event& event) const;
	bool isMouseInside() const;
	void handleSetFocus();
	void handleUnsetFocus();
	bool isFocusedAndKeyPressed(sf::Event& event) const;
	void refreshRenderedText();
	void handleKeys(sf::Event& event);
	char getCharFromEventOrHandleBackspace(sf::Event& event);
	void handleBackspace();
	void appendCharToRealTextIfAllowedChar(char ch);
	bool isAllowedChar(char ch) const;
	bool isToupper(char ch) const;
	bool isShiftPressed() const;
	void appendCharToRealText(char ch);

public:
	TextField(std::shared_ptr<sf::RenderWindow> window);
	virtual void handleEvents(sf::Event & event);
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	inline sf::String getString() { return text.getString(); }

	void setDimensions(float width, float height);
	void setPosition(sf::Vector2f coordinates) override;
};

#endif