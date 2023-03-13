#pragma once
#include "SFML/Graphics.hpp"
class Game
{
private:
	//Variable
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	//Game objects
	sf::RectangleShape character;
	void initVariable();
	void initWindow();
	void initCharacter();
	float speed;
	//bool canJump=true;
	//float jumpHeight=100.0f;

public:
	Game();
	virtual ~Game();

	const bool getWindowIsOpen() const;
	void update();
	void pollEvents();
	void render();
	void moveCharacter();
};