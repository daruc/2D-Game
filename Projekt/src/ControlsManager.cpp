#include <fstream>
#include <iostream>

#include "ControlsManager.h"


namespace
{
	const char* CONTROLS_FILE = "controls.bin";
}

void ControlsManager::load()
{
	std::ifstream fin;
	fin.open(CONTROLS_FILE, std::fstream::binary | std::fstream::in);
	if (!fin.is_open())
	{
		std::cout << "Cannot load controls.bin file.\n";
	}

	int key;
	char* buffer = new char[16];
	fin.read(buffer, 16);
	memcpy(&key, buffer, 4);
	key_left = static_cast<sf::Keyboard::Key>(key);
	memcpy(&key, buffer + 4, 4);
	key_right = static_cast<sf::Keyboard::Key>(key);
	memcpy(&key, buffer + 8, 4);
	key_crouch = static_cast<sf::Keyboard::Key>(key);
	memcpy(&key, buffer + 12, 4);
	key_jump = static_cast<sf::Keyboard::Key>(key);

	delete[] buffer;
	fin.close();
}

void ControlsManager::save()
{
	std::ofstream fout;
	fout.open(CONTROLS_FILE, std::fstream::out | std::fstream::binary | std::fstream::trunc);
	if (!fout.is_open())
	{
		std::cout << "Cannot open controls.bin file.\n";
	}

	int key = static_cast<int>(key_left);
	char bytes[4];
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	key = static_cast<int>(key_right);
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	key = static_cast<int>(key_crouch);
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	key = static_cast<int>(key_jump);
	memcpy(bytes, &key, sizeof(key));
	fout.write(bytes, sizeof(bytes));

	fout.close();
}