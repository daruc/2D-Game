#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Binary.h"
#include "Fixture.h"
#include "ControlsManager.h"


class b2Body;
class b2Fixture;
class b2World;
class Map;


class Player : public Updatable, public Drawable, public Binary, public Fixture
{
private:
	enum Anim {
		RIGHT = 0, LEFT = 1, CROUCH_RIGHT = 2, CROUCH_LEFT = 3
	};

	AnimatedSprite sprite;
	sf::Sprite pistol;
	sf::Texture texture;
	sf::Texture texture_pistol;
	unsigned int bullets;
	unsigned int health;
	const unsigned int max_bullets;
	bool crouch;
	bool can_jump;
	std::shared_ptr<sf::RenderWindow> window;

	b2World* b2world;
	b2Fixture* b2fixture;
	b2Body* b2body;
	std::shared_ptr<Map> map;

	bool win;
	bool dead;
	float max_speed;
	float max_crouch_speed;

	ControlsManager controls_manager;

	void configureAnimations();
	void assignSpritePositionToFixturePosition();
	void handleControls();
	void handleCrouchControls();

	void goLeft();
	void playAnimationGoLeftForward();
	void playAnimationGoLeftBackward();
	void applyForceGoLeft();
	void playAnimationCrouchGoLeftForward();
	void playAnimationCrouchGoLeftBackward();
	void applyForceCrouchGoLeft();

	void goRight();
	void playAnimationGoRightForward();
	void playAnimationGoRightBackward();
	void applyForceGoRight();
	void playAnimationCrouchGoRightBackward();
	void playAnimationCrouchGoRightForward();
	void applyForceCrouchGoRight();

	void stopLeft();
	void stopRight();

	void goJump();

	bool isLookingLeft() const;
	void updatePistolRotation();

	void initFixture();
	void initCrouchFixture();

public:
	Player(std::shared_ptr<sf::RenderWindow> window);
	~Player();
	void initFixture(b2World* b2world, std::shared_ptr<Map> map);
	void beginContact(b2Contact* contact) override;
	void endContact(b2Contact* contact) override;
	void update(float delta_seconds) override;
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const;


	bool shoot();

	inline int getHealth() { return health; }
	inline int getBullets() { return bullets; }
	void setCrouch(bool crouch);
	inline bool getCrouch() { return crouch; }
	bool reload();

	std::vector<char> toBinary() const override;
	void fromBinary(char* bytes) override;
	size_t binarySize() const override;

	inline bool isWin() const { return win; }
	inline bool isDead() const { return dead; }
};

#endif
