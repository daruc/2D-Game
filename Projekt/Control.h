#ifndef CONTROL_H
#define CONTROL_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class Control
{
protected:
	std::shared_ptr <sf::RenderWindow> window;
	std::function<void(std::string)> listener;
public:
	Control(std::shared_ptr <sf::RenderWindow> window) { this->window = window; }
	virtual void update() = 0;
	virtual void draw() = 0;
	inline void addListener(std::function<void(std::string)> listener) { this->listener = listener; }
};

#endif