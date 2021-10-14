#ifndef CONTROL_H
#define CONTROL_H

#include <memory>
#include <functional>

#include <SFML/Graphics.hpp>

#include "../Drawable.h"
#include "../Updatable.h"


class Control : public Updatable, public Drawable
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	std::function<void(std::string)> listener;

public:
	Control(std::shared_ptr<sf::RenderWindow> window);
	virtual void handleEvents(sf::Event & event) = 0;
	void addListener(std::function<void(std::string)> listener);
	virtual void setPosition(sf::Vector2f position) = 0;
};

#endif