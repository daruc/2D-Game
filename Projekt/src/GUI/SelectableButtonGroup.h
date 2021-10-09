#ifndef SELECTABLE_BUTTON_GROUP_H
#define SELECTABLE_BUTTON_GROUP_H

#include <vector>
#include <memory>

#include "SelectableButton.h"


class SelectableButtonGroup
{
private:
	std::vector<std::shared_ptr<SelectableButton>> buttons;

public:
	void addSelectableButton(std::shared_ptr<SelectableButton> selectableButton);
	void unselectAll();
};

#endif // !SELECTABLE_BUTTON_GROUP_H
