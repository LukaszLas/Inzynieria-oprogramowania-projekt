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
	vector<sf::RectangleShape> abysses;
	sf::RectangleShape platform;
	sf::RectangleShape abyss;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Font font;
	sf::Text text;
	//Image
	
	//Initialization
	void initVariable();
	void initWindow();
	void initCharacter();
	void initObjects();
	void initTexture();
	void createPlatform(float sizeX, float sizeY, float positionX, float positionY);
	void initSprite();
	//void initFont();
	//void initText();

	//Variable
	sf::Vector2f velocity;
	bool canJump = true;
	float gravity = 50.5f;
	float jumpHeight = 3.0f;

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
	sf::IntRect uvRect;
};
