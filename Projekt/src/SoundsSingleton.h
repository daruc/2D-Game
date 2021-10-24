#ifndef SOUNDS_SINGLETON_H
#define SOUNDS_SINGLETON_H

#include <SFML/Audio.hpp>
#include <memory>

class SoundsSingleton
{
protected:
	int volume;
	sf::SoundBuffer hit_enemy_buffer;

	SoundsSingleton();

public:
	static SoundsSingleton* getInstance();
	sf::SoundBuffer* getHitEnemyBuffer();
	int getVolume() const;
};

#endif