#include <cstdlib>
#include <ctime>
#include "Blood.h"

Blood::Blood(float x, float y)
{
	srand(time(NULL));

	out_of_date = false;
	for (int i = 0; i < DROPS; ++i)
	{
		int size = (rand() % 6) + 1;
		drop[i] = std::make_shared<sf::RectangleShape>();
		drop[i]->setFillColor(sf::Color::Red);
		drop[i]->setSize(sf::Vector2f(size, size));
		drop[i]->setPosition(x, y);

		sf::Vector2f vec;
		vec.x = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
		vec.x *= 2;
		vec.x -= 1;
		vec.y = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
		vec.y *= 2;
		vec.y -= 1;

		vector[i] = vec;
	}

	lastUpdateTime = sf::Time::Zero;
}

void Blood::update()
{
	float seconds = clock.getElapsedTime().asSeconds();
	if (seconds > SHOW_TIME) out_of_date = true;

	sf::Time deltaTime = clock.getElapsedTime() - lastUpdateTime;
	float deltaMilliseconds = deltaTime.asMilliseconds();

	//gravitation
	for (int i = 0; i < DROPS; ++i)
	{
		vector[i].y += deltaMilliseconds / 200.0f;
	}

	float transparency = seconds / SHOW_TIME;
	for (int i = 0; i < DROPS; ++i)
	{
		sf::Vector2f vec = vector[i];
		vec.x *= deltaMilliseconds/3;
		vec.y *= deltaMilliseconds/3;
		drop[i]->move(vec);
		drop[i]->setFillColor(sf::Color(255, 0, 0, 255 - 255 *transparency));
	}

	lastUpdateTime = clock.getElapsedTime();
}

void Blood::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < DROPS; ++i)
	{
		window.draw(*drop[i]);
	}
}