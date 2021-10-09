#include "SelectableButtonGroup.h"


void SelectableButtonGroup::addSelectableButton(std::shared_ptr<SelectableButton> selectableButton)
{
	selectableButton->setSelectableButtonGroup(this);
	buttons.push_back(selectableButton);
}

void SelectableButtonGroup::unselectAll()
{
	for (std::shared_ptr<SelectableButton> button : buttons)
	{
		button->unselect();
	}
}