#ifndef KEY_FIELD_H
#define KEY_FIELD_H

#include <memory>

#include "Control.h"


class KeyField : public Control
{
private:
	sf::Keyboard::Key key;
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::Text description;
	sf::Font font;
	bool focus;

	void initRectangle();
	void initKeyText();
	void initDescription();
	void handleKeys(sf::Event & event);
	bool isMouseButtonReleased(sf::Event& event) const;
	void setFocus();
	void unsetFocus();
	bool isMouseInsideRectangle() const;
	bool isFocusedKeyPressed(sf::Event& event) const;
	void assignKey(sf::Event& event);
	void setTextPosition();

public:
	KeyField(std::shared_ptr<sf::RenderWindow> window);
	KeyField(std::shared_ptr<sf::RenderWindow> window, sf::Keyboard::Key key);
	virtual void handleEvents(sf::Event & event);
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setDimensions(float width, float height);
	void setPosition(sf::Vector2f position) override;
	void setDescription(std::wstring str);
	inline sf::Keyboard::Key getKey() const { return key; }
};
#endif