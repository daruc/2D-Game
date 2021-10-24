#include <iostream>

#include "SoundsSingleton.h"


SoundsSingleton::SoundsSingleton()
{
	if (!hit_enemy_buffer.loadFromFile("sounds\\hit_enemy.wav"))
	{
		std::cout << "Cannot load file hit_enemy.wav\n";
	}
	volume = 20;
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