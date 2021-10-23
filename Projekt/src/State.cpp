#include "State.h"
#include "App.h"
#include "TexturesSingleton.h"


State::State(std::shared_ptr<sf::RenderWindow> window)
{
	this->window = window;
	this->nextState = nullptr;
}

State::~State()
{
}