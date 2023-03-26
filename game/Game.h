#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
using namespace std;

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game objects
	sf::RectangleShape character;
	sf::RectangleShape testing_ground;
	vector<sf::RectangleShape> platforms;
	sf::RectangleShape platform;
	void initVariable();
	void initWindow();
	void initCharacter();
	void initObjects();
	//Variable
	sf::Vector2f velocity;
	bool canJump = true;
	float gravity = 3.5f;
	float dt;
	sf::Clock dt_clock;
	float moveSpeed = 350.0f;
	const float window_width = 1920;
	const float window_height = 1080;
	sf::FloatRect nextPos;
public:
	Game();
	virtual ~Game();
	
	const bool getWindowIsOpen() const;
	void update();
	void pollEvents();
	void render();
	void moveCharacter();
	float getDT() { return dt; }

};
