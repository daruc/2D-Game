#include "GridLayout.h"
#include "Control.h"


namespace
{
	const float CONTROLS_OFFSET = 120.0f;
}

GridLayout::GridLayout(size_t columns)
	: COLUMNS(columns)
{

}

void GridLayout::handleEvent(sf::Event& event)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->handleEvents(event);
	}
}

void GridLayout::draw(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->draw(window);
	}
}

void GridLayout::update(float delta_seconds)
{
	for (std::shared_ptr<Control> control : controls)
	{
		control->update(delta_seconds);
	}
}

void GridLayout::addControl(std::shared_ptr<Control> control)
{
	setPositionOfControl(control);
	controls.push_back(control);
}

void GridLayout::setPositionOfControl(std::shared_ptr<Control> control)
{
	sf::Vector2f control_position;
	int control_index = controls.size();
	int column_index = control_index % COLUMNS;
	int row_index = control_index / COLUMNS;
	control_position.x = position.x + CONTROLS_OFFSET * column_index;
	control_position.y = position.y + CONTROLS_OFFSET * row_index;
	control->setPosition(control_position);
}

void GridLayout::setPosition(sf::Vector2f position)
{
	this->position = position;
}
