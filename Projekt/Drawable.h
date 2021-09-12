#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>


namespace sf
{
	class RenderWindow;
}

class Drawable
{
public:
	virtual void draw(std::shared_ptr<sf::RenderWindow> window) = 0;
	virtual ~Drawable() {}
};

#endif // !DRAWABLE

