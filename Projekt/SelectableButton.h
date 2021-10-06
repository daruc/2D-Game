#ifndef SELECTABLE_BUTTON_H
#define SELECTABLE_BUTTON_H

#include "Button.h"


class SelectableButtonGroup;

class SelectableButton : public Button
{
private:
	bool selected;
	sf::RectangleShape selection_indicator;
	SelectableButtonGroup* selectable_button_group;

	void updateSelectionIndicatorPosition();

public:
	SelectableButton(std::shared_ptr<sf::RenderWindow> window, std::wstring title);
	void select();
	void unselect();
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void handleEvents(sf::Event & event);
	void setDimensions(float width, float height);
	void setCoordinates(float x, float y);
	void setSelectableButtonGroup(SelectableButtonGroup* selectable_button_group);
};

#endif // !SELECTABLE_BUTTON_H
