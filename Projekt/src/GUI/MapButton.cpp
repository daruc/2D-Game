#include "MapButton.h"
#include "../TexturesSingleton.h"


MapButton::MapButton(std::shared_ptr<sf::RenderWindow> window, std::string title)
	: Button(window, title), completed(false)
{
	TexturesSingleton* textures = TexturesSingleton::getInstance();
	textures->loadTick();
	completed_sprite.setTexture(*textures->getTick());
}

MapButton::MapButton(std::shared_ptr<sf::RenderWindow> window, std::wstring title)
	: Button(window, title), completed(false)
{
	TexturesSingleton* textures = TexturesSingleton::getInstance();
	textures->loadTick();
	completed_sprite.setTexture(*textures->getTick());
}

void MapButton::handleEvents(sf::Event& event)
{
	Button::handleEvents(event);
}

void MapButton::update(float delta_seconds)
{
	Button::update(delta_seconds);
}

void MapButton::draw(std::shared_ptr<sf::RenderWindow> window)
{
	Button::draw(window);
	if (completed)
	{
		window->draw(completed_sprite);
	}
}

void MapButton::setDimensions(sf::Vector2f dimensions)
{
	Button::setDimensions(dimensions);
	updateCompletedSpriteCoordinates();
}

void MapButton::setPosition(sf::Vector2f position)
{
	Button::setPosition(position);
	updateCompletedSpriteCoordinates();
}

void MapButton::updateCompletedSpriteCoordinates()
{
	sf::Vector2f coordinates = Button::getCoordinates()
		+ Button::getDimensions()
		- sf::Vector2f(completed_sprite.getTexture()->getSize());

	completed_sprite.setPosition(coordinates);
}

void MapButton::setCompleted(bool completed)
{
	this->completed = completed;
}