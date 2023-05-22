#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace sf;


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

class classCoin
{
private:
	bool isCollected = false;
	bool isVisible = false;
public:
	sf::CircleShape coin;
	void setCoinRadius(float radius) { this->coin.setRadius(radius); }
	void setCoinPosition(float x, float y) { this->coin.setPosition(x, y); }
	void setCoinTexture(sf::Texture& texture) { this->coin.setTexture(&texture); }
	void setIsCollected() { this->isCollected = true; }
	void setIsVisible(int option) 
	{
		if (option == 1) this->isVisible = true; 
		else if (option == 0) this->isVisible = false;
	}
	sf::FloatRect getCoinGlobalBounds() { return this->coin.getGlobalBounds(); }
	bool getIsCollected() { return this->isCollected; }
	bool getIsVisible() { return this->isVisible; }
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
	sf::Sprite lavaSprite;
	sf::Texture lavaTexture;

	//Traps
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

	vector<classCoin> coins;
	sf::Sprite coinSprite;
	sf::Texture coinTexture;

	sf::RectangleShape endOfLevel;
	sf::Sprite endOfLevelSprite;
	sf::Texture endOfLevelTexture;

	sf::RectangleShape endOfGame;
	sf::Sprite endOfGameSprite;
	sf::Texture endOfGameTexture;

	sf::RectangleShape shop;
	sf::Sprite shopSprite;
	sf::Texture shopTexture;

	//UI
	sf::Font font;
	sf::Text deathCounterText;
	sf::Text TimerText;
	sf::Text currentLevelText;
	sf::Text totalCoinsText;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	//Audio
	sf::Music music;
	sf::SoundBuffer jumpBuffer;
	sf::Sound jumpSound;
	sf::SoundBuffer spikeTrapBuffer;
	sf::Sound spikeTrapSound;
	sf::SoundBuffer coinPickUpBuffer;
	sf::Sound coinPickUpSound;
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
	void initCoins();
	void createMovingEnemies(float positionX, float positionY, float moveRangeRight, float moveRangeLeft);
	void createSpikeTrap(float sizeX, float positionX, float positionY);
	void createAbyss(float sizeX, float sizeY, float positionX, float positionY, string typeTexture);
	void createEndOfLevel(float sizeX, float sizeY, float positionX, float positionY);
	void createEndOfGame(float sizeX, float sizeY, float positionX, float positionY);
	void createCoin(float radius, float positionX, float positionY, int visibility);
	void createShop(float sizeX, float sizeY, float positionX, float positionY);
	void initFont();
	void initText();
	void initTimerText();
	void initAudio();
	void initSound();

	string getAsString();
	void saveGame();
	void loadGame();

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
	clock_t totalTime=clock();
	int deathCounter = 0;
	int spikeTrapTimer = 0;
	//float spikeTrapMoveRange = 20;
	bool moveUp = true;
	float startingpos;
	int currentLevel = 0;
	bool levelUpdate = true;
	int totalCoins = 0;
	bool gameEnded = false;
	bool byShop = false;
	ofstream gameSave;
	ifstream gameLoad;
	ofstream highscorefile;

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
	void setCurrentLevel(int i) { this->currentLevel = i; }
	sf::IntRect uvRect;
};

class result
{
private:
	string deaths;
	string time;
	float best;
public:
	result(string _deaths, string _time, float _best) { this->deaths = _deaths;  this->time = _time; this->best = _best;}
	friend std::ostream& operator<<(std::ostream& os, const result& res)
	{
		os << "Deaths: " << res.deaths << ", Time: " << res.time << ", Best: " << res.best <<endl;
		return os;
	}
	bool operator<(const result& other) const
	{
		return best < other.best;
	}
	bool operator>(const result& other) const
	{
		return best > other.best;
	}
	string getDeaths() { return this->deaths; }
	string getTime() { return this->time; }
	float getBest() { return this->best; }
	string getBestStr() 
	{
		string x= to_string(this->best);
		x=x.substr(0,6);
		cout << x;
		return x;
	}
};
class menuHighScore
{
private:

	sf::RenderWindow windowMenuHighScore;
	sf::Font font;
	Text highScoreTextDeath;
	Text highScoreTextTotal;
	Text highScoreTextBest;
	vector<result> Results;
	vector<sf::Text> textsDeath;
	vector<sf::Text> textsTotal;
	vector<sf::Text> textsBest;
	Texture backgroundTexture;
	Sprite backgroundSprite;
	void loadHighScores();
	void showHighScores();

public:
	void initBackground();

	menuHighScore()
	{
		windowMenuHighScore.create(sf::VideoMode::getFullscreenModes()[0], "Fullscreen Window", sf::Style::Fullscreen);
		font.loadFromFile("Fonts/arial.ttf");
	}
	void run()
	{
		loadHighScores();

		while (windowMenuHighScore.isOpen())
		{
			sf::Event event;
			while (windowMenuHighScore.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					windowMenuHighScore.close();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					windowMenuHighScore.close();
				}
			}
			windowMenuHighScore.clear();
			initBackground();
			showHighScores();

			windowMenuHighScore.display();
		}


	}

};