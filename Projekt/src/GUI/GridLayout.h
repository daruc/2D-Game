#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "../Drawable.h"
#include "../Updatable.h"


class Control;

class GridLayout : public Drawable, public Updatable
{
private:
	const size_t COLUMNS;
	sf::Vector2f position;
	std::vector<std::shared_ptr<Control>> controls;

	void setPositionOfControl(std::shared_ptr<Control> control);

public:
	GridLayout(size_t columns);
	void handleEvent(sf::Event& event);
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float delta_seconds) override;
	void addControl(std::shared_ptr<Control> control);
	void setPosition(sf::Vector2f position);
};

#endif