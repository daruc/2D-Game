#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include <SFML/Graphics.hpp>


class Animation
{
private:
	bool play_forward;
	bool is_looped;
	std::vector<sf::IntRect> frames;
	int current_frame;

	sf::IntRect inrementAndGetFrame();
	sf::IntRect decrementAndGetFrame();

public:
	Animation();
	void addFrame(sf::IntRect rectangle);
	//Looped animation
	inline void setLoop(bool is_looped) { this->is_looped = is_looped; }
	void setDirection(bool play_forward) { this->play_forward = play_forward; }
	bool getDirection() { return play_forward; }
	sf::IntRect nextFrame();
	bool hasNext() const;	//Checks if next frame exists.
	void reset();	//If play_forward = true, returns to beginning, otherwise to end.
};

#endif