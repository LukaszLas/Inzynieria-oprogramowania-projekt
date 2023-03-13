#pragma once
#include "SFML/Graphics.hpp"

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	//Game objects
	sf::RectangleShape character;
	void initVariable();
	void initWindow();
	void initCharacter();
	//Variable
	sf::Vector2f velocity;
	sf::Clock clock;
	int groundHeight = 450;
	float moveSpeed = 10.0f;
	float jumpSpeed = 100.0f;
	float gravity = 1;
	bool canJump=true;
	float jumpHeight=10.0f;

public:
	Game();
	virtual ~Game();

	const bool getWindowIsOpen() const;
	void update();
	void pollEvents();
	void render();
	void moveCharacter();
};