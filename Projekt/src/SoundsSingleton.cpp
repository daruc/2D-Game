#include <iostream>

#include "SoundsSingleton.h"


namespace
{
	const std::string HIT_ENEMY_FILE("sounds\\hit_enemy.wav");
	const int VOLUME = 20;
}


SoundsSingleton::SoundsSingleton()
{
	if (!hit_enemy_buffer.loadFromFile(HIT_ENEMY_FILE))
	{
		std::cout << "Cannot load file hit_enemy.wav\n";
	}
	volume = VOLUME;
}

SoundsSingleton* SoundsSingleton::getInstance()
{
	static SoundsSingleton instance;
	return &instance;
}

sf::SoundBuffer* SoundsSingleton::getHitEnemyBuffer()
{
	return &hit_enemy_buffer;
}

int SoundsSingleton::getVolume() const
{
	return volume;
}