#ifndef CONTROLS_MANAGER_H
#define CONTROLS_MANAGER_H

#include <SFML/Window.hpp>

class ControlsManager
{
private:
	sf::Keyboard::Key key_left;
	sf::Keyboard::Key key_right;
	sf::Keyboard::Key key_jump;
	sf::Keyboard::Key key_crouch;

public:
	void load();
	void save();

	inline sf::Keyboard::Key getLeft() const
	{
		return key_left;
	}

	inline sf::Keyboard::Key getRight() const
	{
		return key_right;
	}

	inline sf::Keyboard::Key getJump() const
	{
		return key_jump;
	}

	inline sf::Keyboard::Key getCrouch() const
	{
		return key_crouch;
	}

	inline void setLeft(sf::Keyboard::Key key)
	{
		key_left = key;
	}

	inline void setRight(sf::Keyboard::Key key)
	{
		key_right = key;
	}

	inline void setJump(sf::Keyboard::Key key)
	{
		key_jump = key;
	}

	inline void setCrouch(sf::Keyboard::Key key)
	{
		key_crouch = key;
	}
};

#endif