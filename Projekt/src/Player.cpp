#include <iostream>
#include <cmath>
#include "Player.h"
#include "Utils/Utils.h"
#include "Map.h"
#include "Fixture.h"
#include "FixtureId.h"


Player::~Player()
{
	if (b2body)
	{
		b2world->DestroyBody(b2body);
	}
}

void Player::initFixture(b2World* b2world, std::shared_ptr<Map> map)
{
	this->map = map;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;

	b2body = b2world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f / 2, 2.0f / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 40.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.3f;
	fixtureDef.userData.pointer = static_cast<uintptr_t>(FixtureId::PLAYER);
	b2fixture = b2body->CreateFixture(&fixtureDef);

	assignSpritePositionToFixturePosition();
}

void Player::assignSpritePositionToFixturePosition()
{
	sf::Vector2f sprite_position = sprite.getPosition();
	b2Vec2 fixture_position;
	fixture_position.x = pixels2Meters(sprite_position.x + 25);
	fixture_position.y = pixels2Meters(sprite_position.y + 50);
	b2body->SetTransform(fixture_position, 0.0f);
}

void Player::beginContact(b2Contact* contact)
{
	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	if (fixture_a != b2fixture && fixture_b != b2fixture)
	{
		return;
	}

	b2Fixture* other_fixture = fixture_a;
	if (fixture_a == b2fixture)
	{
		other_fixture = fixture_b;
	}

	if (fixtureHasId(other_fixture, FixtureId::FINISH))
	{
		std::cout << "game over\n";
		win = true;
	}
	else if (fixtureHasId(other_fixture, FixtureId::FIRE))
	{
		std::cout << "fire\n";
		dead = true;
	}
}

void Player::configureAnimations()
{
	sf::IntRect rect;
	rect.height = 100;
	rect.width = 50;

	rect.left = 0;
	rect.top = 0;

	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(RIGHT, rect);
		rect.left += rect.width;
	}
	rect.top = 100;
	rect.left = 450;
	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(LEFT, rect);
		rect.left -= rect.width;
	}

	rect.height = 50;
	rect.left = 0;
	rect.top = 200;
	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(CROUCH_RIGHT, rect);
		rect.left += rect.width;
	}
	rect.top = 250;
	rect.left = 450;
	for (int i = 0; i < 10; ++i)
	{
		sprite.addFrame(CROUCH_LEFT, rect);
		rect.left -= rect.width;
	}

	sprite.setSpeed(12);
	sprite.setRepeated(RIGHT);
	sprite.setRepeated(LEFT);
	sprite.setRepeated(CROUCH_RIGHT);
	sprite.setRepeated(CROUCH_LEFT);

	sprite.selectAnimation(LEFT);
}

Player::Player(std::shared_ptr<sf::RenderWindow> window)
	: max_bullets(10), sprite(6), b2world(nullptr), map(nullptr), b2fixture(nullptr), b2body(nullptr), win(false), dead(false)
{
	controls_manager.load();
	bullets = max_bullets;
	health = 3;
	max_speed = 3.0f;
	crouch = false;
	this->window = window;

	if (!texture_pistol.loadFromFile("graphics\\pistol.png"))
	{
		std::cout << "Cannot load pistol.png\n";
	}
	pistol.setTexture(texture_pistol);
	pistol.setOrigin(sf::Vector2f(5.0f, 5.0f));

	if (!texture.loadFromFile("graphics\\player.png"))
	{
		std::cout << "Cannot load player.png\n";
	}
	sprite.loadTexture(texture);
	float width = meters2pixels(1.0f);
	float height = meters2pixels(2.0f);
	sprite.setOrigin(sf::Vector2f(width / 2, height / 2));
	configureAnimations();
}

void Player::update(float delta_seconds)
{
	sprite.update(delta_seconds);
	updatePistolRotation();

	if (isLookingLeft())
	{
		sf::Vector2u size = texture_pistol.getSize();
		sf::IntRect rect = sf::IntRect(0, size.y, size.x, -size.y);
		pistol.setTextureRect(rect);
		pistol.setOrigin(sf::Vector2f(5.0f, 16.0f));
	}
	else
	{
		sf::Vector2u size = texture_pistol.getSize();
		sf::IntRect rect = sf::IntRect(0, 0, size.x, size.y);
		pistol.setTextureRect(rect);
		pistol.setOrigin(sf::Vector2f(5.0f, 5.0f));
	}

	if (b2body)
	{
		handleControls();

		sf::Vector2f sprite_position;
		sprite_position.x = meters2pixels(b2body->GetPosition().x);
		sprite_position.y = meters2pixels(b2body->GetPosition().y);
		sprite.setPosition(sprite_position);

		pistol.setPosition(sprite_position);
	}
}

void Player::updatePistolRotation()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2i center = sf::Vector2i(window->getSize().x, window->getSize().y) / 2;
	int width = mouse.x - center.x;
	int height = mouse.y - center.y;

	double rad_angle = atan2(height, width);
	double deg_angle = rad2Deg(rad_angle);

	pistol.setRotation(deg_angle);
}

void Player::handleControls()
{
	if (sf::Keyboard::isKeyPressed(controls_manager.getLeft()))
	{
		goLeft();
	}
	else if (sf::Keyboard::isKeyPressed(controls_manager.getRight()))
	{
		goRight();
	}
	else if (sf::Keyboard::isKeyPressed(controls_manager.getJump()))
	{
		goJump();
	}
	else if (sf::Keyboard::isKeyPressed(controls_manager.getCrouch()))
	{
		goCrouch();
	}
	else if (isLookingLeft())
	{
		stopLeft();
	}
	else
	{
		stopRight();
	}
}

void Player::draw(std::shared_ptr<sf::RenderWindow> window)
{
	sprite.draw(window);
	window->draw(pistol);
}

void Player::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
	sf::Vector2f pistol_pos = pos;
	pistol_pos.x += meters2pixels(0.04f);
	pistol_pos.y += meters2pixels(-0.08f);
	pistol.setPosition(pistol_pos);

	if (b2body)
	{
		b2Vec2 fixture_position;
		fixture_position.x = pixels2Meters(pos.x + 25);
		fixture_position.y = pixels2Meters(pos.y + 50);
		b2body->SetTransform(fixture_position, 0.0f);
	}
}

sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

void Player::goLeft()
{
	if (isLookingLeft())
	{
		playAnimationGoLeftForward();
	}
	else
	{
		playAnimationGoLeftBackward();
	}

	applyForceGoLeft();
}

void Player::playAnimationGoLeftForward()
{
	sprite.selectAnimation(LEFT);
	sprite.setDirection(LEFT, true);
	sprite.stopAnimation(false);
}

void Player::playAnimationGoLeftBackward()
{
	sprite.selectAnimation(RIGHT);
	sprite.setDirection(RIGHT, false);
	sprite.stopAnimation(false);
}

void Player::applyForceGoLeft()
{
	b2Vec2 velocity = b2body->GetLinearVelocity();

	if (velocity.x >= 0)
	{
		b2body->ApplyForce(b2Vec2(-1000.0f, 0.f), b2body->GetWorldCenter(), true);
	}
	else if (velocity.x >= -max_speed)
	{
		b2body->ApplyForce(b2Vec2(-10000.0f, 0.f), b2body->GetWorldCenter(), true);
	}
}

bool Player::isLookingLeft() const
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	return mouse_pos.x <= window->getSize().x / 2.0f;
}

void Player::goRight()
{
	if (isLookingLeft())
	{
		playAnimationGoRightBackward();
	}
	else
	{
		playAnimationGoRightForward();
	}
	applyForceGoRight();
}

void Player::playAnimationGoRightBackward()
{
	sprite.selectAnimation(LEFT);
	sprite.setDirection(LEFT, false);
	sprite.stopAnimation(false);
}

void Player::playAnimationGoRightForward()
{
	sprite.selectAnimation(RIGHT);
	sprite.setDirection(RIGHT, true);
	sprite.stopAnimation(false);
}

void Player::applyForceGoRight()
{
	b2Vec2 velocity = b2body->GetLinearVelocity();
	if (velocity.x <= 0)
	{
		b2body->ApplyForce(b2Vec2(1000.0f, 0.f), b2body->GetWorldCenter(), true);
	}
	else if (velocity.x <= max_speed)
	{
		b2body->ApplyForce(b2Vec2(10000.0f, 0.f), b2body->GetWorldCenter(), true);
	}
}

void Player::stopLeft()
{
	sprite.selectAnimation(LEFT);
	sprite.setDirection(LEFT, true);
	sprite.stopAnimation(true);
}

void Player::stopRight()
{
	sprite.selectAnimation(RIGHT);
	sprite.setDirection(RIGHT, true);
	sprite.stopAnimation(true);
}

void Player::goCrouchLeft()
{
	sprite.selectAnimation(CROUCH_LEFT);
	if (sprite.getDirection(CROUCH_LEFT) == false)
	{
		sprite.setDirection(CROUCH_LEFT, true);
	}
	sprite.stopAnimation(false);
}

void Player::goCrouchRight()
{
	sprite.selectAnimation(CROUCH_RIGHT);
	if (sprite.getDirection(CROUCH_RIGHT) == false)
	{
		sprite.setDirection(CROUCH_RIGHT, true);
	}
	sprite.stopAnimation(false);
}

void Player::stopCrouchLeft()
{
	sprite.selectAnimation(CROUCH_LEFT);
	sprite.setDirection(CROUCH_LEFT, true);
	sprite.stopAnimation(true);
}

void Player::stopCrouchRight()
{
	sprite.selectAnimation(CROUCH_RIGHT);
	sprite.setDirection(CROUCH_RIGHT, true);
	sprite.stopAnimation(true);
}

void Player::goCrouchLeftBack()
{
	sprite.selectAnimation(CROUCH_RIGHT);
	if (sprite.getDirection(CROUCH_RIGHT))
	{
		sprite.setDirection(CROUCH_RIGHT, false);
	}

	sprite.stopAnimation(false);
}

void Player::goCrouchRightBack()
{
	sprite.selectAnimation(CROUCH_LEFT);
	if (sprite.getDirection(CROUCH_LEFT))
	{
		sprite.setDirection(CROUCH_LEFT, false);
	}
	sprite.stopAnimation(false);
}

bool Player::shoot()
{
	if (bullets > 0)
	{
		--bullets;
		return true;
	}

	return false;
}

bool Player::reload()
{
	if (bullets == 0)
	{
		bullets = max_bullets;
		return true;
	}

	return false;
}

void Player::setCrouch(bool crouch)
{
	this->crouch = crouch;

	sf::Vector2f pos;
	if (crouch == true)
	{
		pos.y = pos.x = meters2pixels(1.0f) / 2.0f;
		sprite.setOrigin(pos);
	}
	else
	{
		pos.x = meters2pixels(1.0f) / 2.0f;
		pos.y = meters2pixels(2.0f) / 2.0f;
		sprite.setOrigin(pos);
	}
}

std::vector<char> Player::toBinary() const
{
	sf::Vector2f position = getPosition();
	std::vector<char> buffer(binarySize());
	memcpy(buffer.data(), &position, sizeof(position));

	return buffer;
}

void Player::fromBinary(char* bytes)
{
	sf::Vector2f position;
	memcpy(&position, bytes, sizeof(position));
	setPosition(position);
}

size_t Player::binarySize() const
{
	return sizeof(getPosition());
}

void Player::goJump()
{
	// TODO
	b2body->ApplyLinearImpulse(b2Vec2(0.0f, -800.0f), b2Vec2(b2body->GetPosition()), true);
}

void Player::goCrouch()
{
	// TODO
}