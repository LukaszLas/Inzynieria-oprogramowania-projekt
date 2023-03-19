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
	void initTestingGround();
	void initObjects();
	//Variable
	sf::Vector2f velocity;
	float dt;
	sf::Clock dt_clock;
	float moveSpeed = 100.0f;
	const float window_width = 800;
	const float window_height = 600;
	float groundHeight = 20.0f;
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