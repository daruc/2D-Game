#include <cstdlib>
#include <ctime>
#include "Blood.h"
#include "Drop.h"


Blood::Blood(sf::Vector2f position)
	: drops(DROPS)
{
	srand(time(NULL));

	for (std::shared_ptr<Drop>& drop : drops)
	{
		drop = std::make_shared<Drop>(position);
	}
}

void Blood::update(float deltaSeconds)
{
	for (std::shared_ptr<Drop> drop : drops)
	{
		drop->update(deltaSeconds);
	}
}

void Blood::draw(std::shared_ptr<sf::RenderWindow> window)
{
	for (std::shared_ptr<Drop> drop : drops)
	{
		drop->draw(window);
	}
}

bool Blood::isReadyToDestroy() const
{
	for (std::shared_ptr<Drop> drop : drops)
	{
		if (!drop->isReadyToDestroy())
		{
			return false;
		}
	}
	return true;
}