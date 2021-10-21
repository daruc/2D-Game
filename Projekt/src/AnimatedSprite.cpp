#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const size_t animations)
{
	animation = new Animation[animations];
	fps = 5;
	selected_animation = 0;
	n_current_frame = 0;
}

AnimatedSprite::~AnimatedSprite()
{
	delete[] animation;
}

void AnimatedSprite::loadTexture(const sf::Texture & texture)
{
	Sprite::setTexture(texture);
}

void AnimatedSprite::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(*this);
}

void AnimatedSprite::addFrame(int n_animation, sf::IntRect frame)
{
	animation[n_animation].addFrame(frame);
}

void AnimatedSprite::update(float delta_seconds)
{
	if (!stop)
	{
		sf::Time elapsedTime = clock.getElapsedTime();
		float elapsedSeconds = elapsedTime.asMilliseconds() / (float)1000;
		int offset = static_cast<int>(fps * elapsedSeconds);

		for (int i = 0; i < offset; ++i)
		{
			sf::IntRect rect = animation[selected_animation].nextFrame();
			sf::Sprite::setTextureRect(rect);
		}

		if (offset >= 1)
		{
			clock.restart();
		}
	}
	else
	{
		animation[selected_animation].reset();
		sf::IntRect rect = animation[selected_animation].nextFrame();
		sf::Sprite::setTextureRect(rect);
	}
	
}

void AnimatedSprite::setRepeated(int n_animation, bool loop)
{
	animation[n_animation].setLoop(loop);
}

void AnimatedSprite::setDirection(int n_animation, bool play_forward)
{
	animation[n_animation].setDirection(play_forward);
}

bool AnimatedSprite::getDirection(int n_animation)
{
	return animation[n_animation].getDirection();
}