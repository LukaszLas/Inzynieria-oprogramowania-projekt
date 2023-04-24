#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <ctime>
#include <iostream>
using namespace std;


class classSpikeTrap
{
private:
	float startPositionY;
	float moveRange=20;
public:
	sf::RectangleShape spikeTrap;
	void setSizeSpikeTrap(float x, float y) { this->spikeTrap.setSize(sf::Vector2f(x, y)); }
	void setPositionSpikeTrap(float x, float y) { this->spikeTrap.setPosition(x, y); }
	void setTextureSpikeTrap(sf::Texture& texture) { this->spikeTrap.setTexture(&texture); }
	void setStartPosYSpikeTrap(float x) { this->startPositionY = x; }
	void setMoveRangeSpikeTrap(float x) { this->moveRange = x; }
	float getStartPositionY() { return this->startPositionY; }
	float getMoveRange() { return this->moveRange; }
};

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game objects
	//Character
	sf::RectangleShape character;
	sf::Texture texture;
	sf::Sprite sprite;
	//Platforms
	sf::Sprite platformSprite;
	sf::Texture platformTexture;
	vector<sf::RectangleShape> platforms;
	sf::RectangleShape platform;
	//Enemies
	sf::Sprite abyssSprite;
	sf::Texture abyssTexture;
	vector<sf::RectangleShape> abysses;
	sf::RectangleShape abyss;
	vector<sf::RectangleShape> movingEnemys;
	sf::RectangleShape movingEnemy ;
	sf::Sprite spikesSprite;
	sf::Texture spikesTexture;
	vector< classSpikeTrap> spikeTraps;
	//sf::RectangleShape spikeTrap;
	sf::Sprite enemySprite;
	sf::Texture movingEnemyTexture;
	
	sf::RectangleShape endOfLevel;
	sf::Sprite endOfLevelSprite;
	sf::Texture endOfLevelTexture;
	

	//UI
	sf::Font font;
	sf::Text deathCounterText;
	sf::Text TimerText;
	sf::Text currentLevelText;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	//Audio
	sf::SoundBuffer jumpBuffer;
	sf::Sound jumpSound;
	sf::SoundBuffer spikeTrapBuffer;
	sf::Sound spikeTrapSound;
	//Image
	
	//Initialization
	void initVariable();
	void initWindow();
	void initCharacter();
	void initObjects();
	void initTexture();
	void createPlatform(float sizeX, float sizeY, float positionX, float positionY);
	void initSprite();
	void initEnemies();
	void createMovingEnemies(float positionX, float positionY, float moveRangeRight, float moveRangeLeft);
	void createSpikeTrap(float sizeX, float positionX, float positionY);
	void createAbyss(float sizeX, float sizeY, float positionX, float positionY);
	void createEndOfLevel(float sizeX, float sizeY, float positionX, float positionY);
	void initFont();
	void initText();
	void initTimerText();
	void initAudio();
	void initSound();

	//Variable
	sf::Vector2f velocity;
	bool canJump = true;
	bool characterRightGoing = true;
	float gravity = 50.5f;
	float jumpHeight = 3.0f;
	float dt;
	sf::Clock dt_clock;
	float moveSpeed = 350.0f;
	const float window_width = 1920;
	const float window_height = 1080;
	sf::FloatRect nextPos;
	float enemyMoveRangeRight;
	float enemyMoveRangeLeft;
	float enemyStartPositionX;
	bool moveRight = true;
	float duration;
	clock_t timeStart =clock();
	int deathCounter = 0;
	int spikeTrapTimer = 0;
	//float spikeTrapMoveRange = 20;
	bool moveUp = true;
	float startingpos;
	int currentLevel = 0;
	bool levelUpdate = true;

public:
	Game();
	virtual ~Game();
	
	const bool getWindowIsOpen() const;
	void update();
	void pollEvents();
	void render();
	void moveCharacter();
	void moveEnemy();
	void moveSpikeTrap();
	float getDT() { return dt; }
	sf::IntRect uvRect;
};

