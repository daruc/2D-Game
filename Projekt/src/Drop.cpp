#include "Drop.h"
#include "Utils/Random.h"


Drop::Drop(sf::Vector2f position)
	: COLOR(sf::Color::Red)
{
	shape.setFillColor(COLOR);
	shape.setSize(getRandomSize());
	shape.setPosition(position);

	velocity = getRandomVelocity();
	secondsToDestroy = SHOW_TIME;
}

sf::Vector2f Drop::getRandomSize() const
{
	int size = randRange(MIN_SIZE, MAX_SIZE);
	return sf::Vector2f(size, size);
}

sf::Vector2f Drop::getRandomVelocity() const
{
	sf::Transform rotation;
	rotation.rotate(randAngleInDegrees());

	sf::Vector2f unitVector(1.0f, 0.0f);
	sf::Vector2f rotatedVector = rotation.transformPoint(unitVector);
	sf::Vector2f scaledVector = rotatedVector * rand01();
	return scaledVector;
}

void Drop::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(shape);
}

void Drop::update(float delta_seconds)
{
	if (isReadyToDestroy())
	{
		return;
	}

	updateSecondsToDestroy(delta_seconds);
	updateGravitation(delta_seconds);
	updateTransparency();
}

void Drop::updateSecondsToDestroy(float delta_seconds)
{
	secondsToDestroy -= delta_seconds;
}

void Drop::updateGravitation(float delta_seconds)
{
	velocity.y += delta_seconds * GRAVITATION;
	sf::Vector2f positionOffset = velocity;
	positionOffset *= delta_seconds / SPEED;
	shape.move(positionOffset);
}

void Drop::updateTransparency()
{
	float transparency = secondsToDestroy / SHOW_TIME;
	sf::Color color = COLOR;
	color.a = MAX_OPACITY * transparency;
	shape.setFillColor(color);
}

bool Drop::isReadyToDestroy()
{
	return secondsToDestroy <= 0.0f;
}