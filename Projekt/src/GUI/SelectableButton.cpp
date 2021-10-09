#include "SelectableButton.h"
#include "SelectableButtonGroup.h"


SelectableButton::SelectableButton(std::shared_ptr<sf::RenderWindow> window, std::wstring title)
	: Button(window, title)
{
	selected = false;
	selectable_button_group = nullptr;
	selection_indicator.setSize(sf::Vector2f(20.0f, 40.0f));
	selection_indicator.setFillColor(sf::Color::Green);
}

void SelectableButton::select()
{
	if (selectable_button_group)
	{
		selectable_button_group->unselectAll();
	}
	selected = true;
}

void SelectableButton::unselect()
{
	selected = false;
}

void SelectableButton::draw(std::shared_ptr<sf::RenderWindow> window)
{
	Button::draw(window);
	if (selected)
	{
		window->draw(selection_indicator);
	}
}

void SelectableButton::handleEvents(sf::Event& event)
{
	if (isMouseButtonReleasedInsideButton(event))
	{
		select();
		listener(text.getString());
	}
}

void SelectableButton::setDimensions(float width, float height)
{
	Button::setDimensions(width, height);
	updateSelectionIndicatorPosition();
}

void SelectableButton::setDimensions(sf::Vector2f dimensions)
{
	Button::setDimensions(dimensions);
	updateSelectionIndicatorPosition();
}

void SelectableButton::setCoordinates(float x, float y)
{
	Button::setCoordinates(x, y);
	updateSelectionIndicatorPosition();
}

void SelectableButton::updateSelectionIndicatorPosition()
{
	sf::Vector2f button_position = rectangle.getPosition();
	sf::Vector2f button_dimensions = rectangle.getSize();
	float selection_indicator_x = button_position.x + button_dimensions.x - selection_indicator.getSize().x;
	float selection_indicator_y = button_position.y;
	selection_indicator.setPosition(selection_indicator_x, selection_indicator_y);
}

void SelectableButton::setSelectableButtonGroup(SelectableButtonGroup* selectable_button_group)
{
	this->selectable_button_group = selectable_button_group;
}