#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Animation.h"
#include "Drawable.h"
#include "Updatable.h"


class AnimatedSprite : private sf::Sprite, public Drawable, public Updatable
{
private:
	Animation * animation;
	sf::Clock clock;
	int fps;
	int selected_animation;
	int n_current_frame;
	bool stop;

public:
	AnimatedSprite(const std::size_t animations);
	~AnimatedSprite();
	void loadTexture(const sf::Texture & texture);
	inline void selectAnimation(int n_animation) { selected_animation = n_animation; }
	void update(float deltaSeconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void addFrame(int n_animation, sf::IntRect frame);
	void setDirection(int n_animation, bool play_forward);
	bool getDirection(int n_animation);
	inline void setSpeed(int fps) { this->fps = fps; }
	void setRepeated(int n_animation, bool loop = true);
	inline void setPosition(sf::Vector2f pos) { sf::Sprite::setPosition(pos); }
	inline void setOrigin(sf::Vector2f origin) { sf::Sprite::setOrigin(origin); }
	inline sf::Vector2f getPosition() const {
		return sf::Sprite::getPosition();
	}

	inline void stopAnimation(bool stop) { this->stop = stop; }
};

#endif