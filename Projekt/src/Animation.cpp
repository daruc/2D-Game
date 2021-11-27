#include "Animation.h"

Animation::Animation()
{
	play_forward = true;
	is_looped = true;
	current_frame = 0;
}

void Animation::addFrame(sf::IntRect rectangle)
{
	frames.push_back(rectangle);
}

sf::IntRect Animation::nextFrame()
{
	if (play_forward)
	{
		return inrementAndGetFrame();
	}

	return decrementAndGetFrame();
}

sf::IntRect Animation::inrementAndGetFrame()
{
	if (is_looped)
	{
		int size = frames.size();
		int temp = current_frame;

		++current_frame;
		if (current_frame >= size)
		{
			current_frame = 0;
		}

		return frames[temp];
	}

	return frames[current_frame++];
}

sf::IntRect Animation::decrementAndGetFrame()
{
	if (is_looped)
	{
		int size = frames.size();

		int temp = current_frame;

		--current_frame;
		if (current_frame < 0)
		{
			current_frame = size - 1;
		}

		return frames[temp];
	}

	return frames[current_frame--];
}

bool Animation::hasNext() const
{
	if (is_looped)
	{
		return true;
	}

	if (play_forward)
	{
		int size = frames.size();
		if (current_frame == size)
		{
			return false;
		}
		return true;
	}

	if (current_frame == -1)
	{
		return false;
	}

	return true;
}

void Animation::reset()
{
	if (play_forward)
	{
		current_frame = 0;
	}
	else
	{
		current_frame = frames.size() - 1;
	}
}