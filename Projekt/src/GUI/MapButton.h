#ifndef MAP_BUTTON_H
#define MAP_BUTTON_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Control.h"


class MapButton : public Button
{
private:
	sf::Sprite completed_sprite;
	bool completed;

	void updateCompletedSpriteCoordinates();

public:
	MapButton(std::shared_ptr<sf::RenderWindow> window, std::string title);
	MapButton(std::shared_ptr<sf::RenderWindow> window, std::wstring title);
	void handleEvents(sf::Event& event) override;
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setDimensions(sf::Vector2f dimensions);
	void setPosition(sf::Vector2f position) override;
	void setCompleted(bool completed);
};

#endif