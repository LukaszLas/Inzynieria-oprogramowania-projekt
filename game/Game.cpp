#include "Game.h"
//Private Functions
void Game::initVariable()
{
	this->window = nullptr;
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	const float window_width = 1920;
	const float window_height = 1080;

}

void Game::initWindow()
{
	this->videoMode.height = window_height;
	this->videoMode.width = window_width;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
}

void Game::initCharacter()
{
	this->character.setPosition(65.f, 825.f);
	this->initTexture();
	this->initSprite();
	this->character.setSize(sf::Vector2f(50.f, 50.f));
	this->character.setTexture(&texture);
}

void Game::initEnemies()
{
	this->movingEnemy.setPosition(650,1250);
	this->initTexture();
	this->initSprite();
	this->movingEnemy.setSize(sf::Vector2f(60.f, 60.f));
	this->movingEnemy.setTexture(&movingEnemyTexture);
	this->enemyMoveRangeRight = 200;
	this->enemyMoveRangeLeft = 200;
	this->enemyStartPositionX = this->movingEnemy.getPosition().x;
	//movingEnemys.push_back(this->movingEnemy);
	//createMovingEnemies(200, 200, 100, 100);
}

void Game::createMovingEnemies(float positionX, float positionY, float moveRangeRight, float moveRangeLeft)
{
	this->movingEnemy.setPosition(positionX, positionY);
	//this->initTexture();
	//this->initSprite();
	this->movingEnemy.setSize(sf::Vector2f(60.f, 60.f));
	this->movingEnemy.setTexture(&movingEnemyTexture);
	this->enemyMoveRangeRight = moveRangeRight;
	this->enemyMoveRangeLeft = moveRangeLeft;
	enemyStartPositionX = movingEnemy.getPosition().x;
	movingEnemys.push_back(this->movingEnemy);
}

void Game::initObjects()
{

	switch (this->currentLevel)
	{
	case -1:
		cout << "xd";
		break;
	case 0:
		platforms.clear();
		abysses.clear();
		spikeTraps.clear();
		movingEnemys.clear();
		coins.clear();
		createPlatform(100, 20, 250, 850);
		createPlatform(100, 20, 370, 700);
		createPlatform(100, 20, 50, 950);
		createPlatform(1920, 7, 0, 1073);
		createPlatform(150, 20, 520, 550);
		createPlatform(100, 20, 750, 425);
		createPlatform(100, 20, 1000, 425);
		createPlatform(40, 20, 1350, 425);
		createSpikeTrap(30, 400, 700);
		createSpikeTrap(30, 450, 700);
		createMovingEnemies(1350, 1020, 160, 160);
		createAbyss(100, 9, 650, 1070);
		createAbyss(100, 9, 830, 1070);
		createAbyss(380, 19, 650, 800);
		createAbyss(420, 9, 150, 1070);
		createAbyss(310, 19, 1070, 500);
		createCoin(20, 1350, 330);
		createCoin(20, 1350, 380);
		createCoin(20, 570, 500);
		createCoin(20, 280, 800);
		createCoin(20, 1775, 1025);
		createEndOfLevel(50, 100, 1870, 980);
		break;
	case 1:
		platforms.clear();
		abysses.clear();
		spikeTraps.clear();
		movingEnemys.clear();
		coins.clear();
		createPlatform(50, 20, 620, 500);
		createPlatform(50, 20, 720, 600);
		createPlatform(50, 20, 850, 700);
		createPlatform(50, 20, 980, 800);
		createPlatform(50, 20, 1200, 900);
		createPlatform(50, 20, 1450, 1000);
		createPlatform(50, 20, 1660, 1100);
		createPlatform(50, 20, 1760, 1200);
		createPlatform(1920, 7, 0, 1073);
		createSpikeTrap(50, 720, 600);
		createAbyss(1680, 9, 0, 1070);
		createEndOfLevel(50, 100, 400, 200);
		break;
	case 2:
		platforms.clear();
		abysses.clear();
		spikeTraps.clear();
		movingEnemys.clear();
		coins.clear();
		createEndOfLevel(50, 100, 400, 2200);
		createEndOfGame(50, 100, 1030, 800);
	default:
		break;
	}

	
	//this->spikeTrap.setFillColor(sf::Color::Magenta);
	//this->spikeTrap.setSize(sf::Vector2f(30.f, 19.f));
	//this->spikeTrap.setPosition(400.f, 700.f);
	//this->spikeTrap.setTexture(&spikesTexture);
	//this->spikeTraps.push_back(this->spikeTrap);
	//startingpos = spikeTrap.getPosition().y;

	//createEndOfLevel(50, 100, 1870, 980);
	
}     

void Game::createPlatform(float sizeX, float sizeY, float positionX, float positionY)
{
	this->platform.setSize(sf::Vector2f(sizeX, sizeY));
	this->platform.setPosition(positionX, positionY);
	this->platform.setTexture(&platformTexture);
	this->platforms.push_back(this->platform);
}

void Game::createAbyss(float sizeX, float sizeY, float positionX, float positionY)
{
	this->abyss.setSize(sf::Vector2f(sizeX, sizeY));
	this->abyss.setPosition(positionX, positionY);
	this->abyss.setTexture(&abyssTexture);
	this->abysses.push_back(this->abyss);
}

void Game::createSpikeTrap(float sizeX, float positionX, float positionY)
{
	classSpikeTrap st;
	st.setPositionSpikeTrap(positionX, positionY);
	st.setSizeSpikeTrap(sizeX, 19);
	st.setTextureSpikeTrap(spikesTexture);
	st.setStartPosYSpikeTrap(st.spikeTrap.getPosition().y);
	spikeTraps.push_back(st);
}

void Game::createEndOfLevel(float sizeX, float sizeY, float positionX, float positionY)
{
	this->endOfLevel.setSize(sf::Vector2f(sizeX, sizeY));
	this->endOfLevel.setTexture(&endOfLevelTexture);
	this->endOfLevel.setPosition(positionX, positionY);
}

void Game::createEndOfGame(float sizeX, float sizeY, float positionX, float positionY)
{
	this->endOfGame.setSize(sf::Vector2f(sizeX, sizeY));
	this->endOfGame.setTexture(&endOfLevelTexture);
	this->endOfGame.setPosition(positionX, positionY);
	this->endOfGame.setFillColor(sf::Color::Red);
}

void Game::createCoin(float radius, float positionX, float positionY)
{
		classCoin coin;
		coin.setCoinRadius(radius);
		coin.setCoinPosition(positionX, positionY);
		coin.setCoinTexture(coinTexture);
		coins.push_back(coin);
}

void Game::initTexture()
{
	if (!this->texture.loadFromFile("Images/image.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->movingEnemyTexture.loadFromFile("Images/cavemanR.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->platformTexture.loadFromFile("Images/platform.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->abyssTexture.loadFromFile("Images/abyss.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->spikesTexture.loadFromFile("Images/spikes.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->backgroundTexture.loadFromFile("Images/background.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->endOfLevelTexture.loadFromFile("Images/door.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->coinTexture.loadFromFile("Images/coin.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->endOfGameTexture.loadFromFile("Images/door.png"))
	{
		cout << "Error initTexture";
	}
}

void Game::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->enemySprite.setTexture(this->movingEnemyTexture);
	this->platformSprite.setTexture(this->platformTexture);
	this->abyssSprite.setTexture(this->abyssTexture);
	this->spikesSprite.setTexture(this->spikesTexture);
	this->endOfLevelSprite.setTexture(this->endOfLevelTexture);
	this->endOfGameSprite.setTexture(this->endOfLevelTexture);
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->coinSprite.setTexture(this->coinTexture);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/arial.ttf"))
	{
		cout << "Error initFont";
	}
}

void Game::initText()
{
	this->deathCounterText.setFont(font);
	this->deathCounterText.setCharacterSize(30);
	this->deathCounterText.setStyle(sf::Text::Bold);
	this->deathCounterText.setPosition(20.f, 80.f);
	this->deathCounterText.setString("Deaths: 0");

	this->currentLevelText.setFont(font);
	this->currentLevelText.setCharacterSize(30);
	this->currentLevelText.setStyle(sf::Text::Bold);
	this->currentLevelText.setPosition(1750.f, 40.f);
	this->currentLevelText.setString("Level: 1");

	this->totalCoinsText.setFont(font);
	this->totalCoinsText.setCharacterSize(30);
	this->totalCoinsText.setStyle(sf::Text::Bold);
	this->totalCoinsText.setPosition(1750.f, 80.f);
	this->totalCoinsText.setString("Coins: 0");
}

void Game::initTimerText()
{
	this->TimerText.setFont(font);
	this->TimerText.setCharacterSize(30);
	this->TimerText.setStyle(sf::Text::Bold);
	this->TimerText.setPosition(20.f, 40.f);
}

void Game::initAudio()
{
	if (!this->jumpBuffer.loadFromFile("Audio/jump.wav"))
	{
		cout << "Error initAudio";
	}
	if (!this->spikeTrapBuffer.loadFromFile("Audio/spiketrap.wav"));
	{
		cout << "Error initAudio";
	}
	if (!this->coinPickUpBuffer.loadFromFile("Audio/coin.wav"));
	{
		cout << "Error initAudio";
	}
	if (!this->music.openFromFile("Audio/horses.ogg"))
	{
		cout << "Error initAudio";
	}
}

void Game::initSound()
{
	this->jumpSound.setBuffer(this->jumpBuffer);
	this->spikeTrapSound.setBuffer(this->spikeTrapBuffer);
	this->coinPickUpSound.setBuffer(this->coinPickUpBuffer);
	this->music.setLoop(true);
	this->music.setVolume(30.f);
	this->music.play();

}

const string Game::getAsString() const
{
	stringstream ss;
	ss << this->character.getPosition().x << " " << this->character.getPosition().y << " " 
	   << this->currentLevel << " " << this->totalCoins << " " << this->deathCounter;
	return ss.str();
}

void Game::saveGame()
{
	this->gameSave.open("Saves/gamesave.txt");
	if (this->gameSave.is_open())
	{
		this->gameSave << getAsString();
	}
	else
	{
		cout << "Error: could not save!";
	}
}

void Game::loadGame()
{
	this->gameLoad.open("Saves/gamesave.txt");
	if (this->gameLoad.is_open())
	{
		sf::Vector2f position;
		int level=0, coins=0, deaths=0;

		this->gameLoad >> position.x >> position.y >> level >> coins >> deaths;

		this->character.setPosition(position);
		this->currentLevel = level;
		this->totalCoins = coins;
		this->deathCounter = deaths;

		this->initObjects();
		this->initText();
	}
	else
	{
		cout << "Error: could not load!";
	}
}


//Constructors /Destructor
Game::Game()
{

	
	this->initVariable();
	this->initWindow();
	this->initCharacter();
	this->initObjects();
	//this->initEnemies();
	this->initFont();
	this->initText();
	this->initTimerText();
	this->initAudio();
	this->initSound();
	
}

Game::~Game()
{
	delete this->window;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::update()
{
	dt = dt_clock.restart().asSeconds();
	this->pollEvents();
	moveCharacter();
	moveEnemy();
	moveSpikeTrap();
	clock_t timeStop = clock();
	duration = static_cast<float>(timeStop - timeStart) / CLOCKS_PER_SEC;
	TimerText.setString(to_string(duration));
	//end of game collision
	sf::FloatRect endOfGameBounds = endOfGame.getGlobalBounds();
	if (endOfGameBounds.intersects(character.getGlobalBounds())&&gameEnded==false)
	{
		highscorefile.open("Saves/highscore.txt");
		highscorefile << deathCounter << " " << static_cast<float>(timeStop - totalTime) / CLOCKS_PER_SEC << " " << duration<<endl;
		highscorefile.close();
		gameEnded = true;
	}
	if (levelUpdate)
	{
		this->initObjects();
		levelUpdate = false;
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			if (this->ev.key.code == sf::Keyboard::F5)
			{
				this->saveGame();
			}
			if (this->ev.key.code == sf::Keyboard::F9)
			{
				this->loadGame();
			}
			break;

		}
	}
}

void Game::render()
{
	this->window->clear();
	//draw game objects
	
	this->window->draw(backgroundSprite);
	this->window->draw(this->character);
	//this->window->draw(this->movingEnemy);
	this->window->draw(this->endOfLevel);
	for (auto& i : this->spikeTraps)
	{
		this->window->draw(i.spikeTrap);
	}
	for (auto& i : this->platforms)
	{
		this->window->draw(i);
	}
	for (auto& i : this->abysses)
	{
		this->window->draw(i);
	}
	for (size_t i = 0; i < this->coins.size(); i++)
	{
		if(this->coins[i].getIsCollected() == false)
		{
			this->window->draw(coins[i].coin);
		}
	}
	for (auto& i : this->movingEnemys)
	{
		this->window->draw(i);
	}
	this->window->draw(this->endOfGame);

	//draw UI
	this->window->draw(this->deathCounterText);
	this->window->draw(this->TimerText);
	this->window->draw(this->currentLevelText);
	this->window->draw(this->totalCoinsText);
	this->window->display();
}




void Game::moveCharacter()
{
	//Key pressed move
	this->character.setSize(sf::Vector2f(50.f, 50.f));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->velocity.x -= moveSpeed * this->getDT();
		this->characterRightGoing = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->velocity.x += moveSpeed * this->getDT();
		this->characterRightGoing = true;

	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (this->canJump == true))
	{
		this->canJump = false;
		this->jumpSound.play();
		this->velocity.y = -sqrt(2.0f * gravity * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->character.setSize(sf::Vector2f(50.f, 35.f));
	}
	this->velocity.y += gravity * dt;

	if (this->characterRightGoing)
		this->texture.loadFromFile("Images/image.png");
	else
		this->texture.loadFromFile("Images/imageL.png");

	//objects collision
	for (auto& platform : platforms)
	{
		sf::FloatRect characterBounds = character.getGlobalBounds();
		sf::FloatRect platformBounds = platform.getGlobalBounds();
		sf::FloatRect abyssBounds = abyss.getGlobalBounds();
		nextPos = characterBounds;
		nextPos.left += velocity.x;
		nextPos.top += velocity.y;

		if (platformBounds.intersects(nextPos))
		{
			//bottom collision
			if (characterBounds.top < platformBounds.top
				&& characterBounds.top + characterBounds.height < platformBounds.top + platformBounds.height
				&& characterBounds.left < platformBounds.left + platformBounds.width
				&& characterBounds.left + characterBounds.width > platformBounds.left)
			{
				velocity.y = 0.f;
				this->canJump = true;
				character.setPosition(characterBounds.left, platformBounds.top - characterBounds.height);
			}
			//top collision
			else if (characterBounds.top > platformBounds.top
				&& characterBounds.top + characterBounds.height > platformBounds.top + platformBounds.height
				&& characterBounds.left < platformBounds.left + platformBounds.width
				&& characterBounds.left + characterBounds.width > platformBounds.left)
			{
				velocity.y = 0.f;
				character.setPosition(characterBounds.left, platformBounds.top + platformBounds.height);
			}
			//right collision
			else if (characterBounds.left < platformBounds.left
				&& characterBounds.left + characterBounds.width < platformBounds.left + platformBounds.width
				&& characterBounds.top < platformBounds.top + platformBounds.height
				&& characterBounds.top + characterBounds.height > platformBounds.top)
			{
				velocity.x = 0.f;
				character.setPosition(platformBounds.left - characterBounds.width, characterBounds.top);
			}
			//left collision
			else if (characterBounds.left > platformBounds.left
				&& characterBounds.left + characterBounds.width > platformBounds.left + platformBounds.width
				&& characterBounds.top < platformBounds.top + platformBounds.height
				&& characterBounds.top + characterBounds.height > platformBounds.top)
			{
				velocity.x = 0.f;
				character.setPosition(platformBounds.left + platformBounds.width, characterBounds.top);
			}
		}
	}
	//abyss collision
	for (auto& abyss : abysses)
	{
		sf::FloatRect abyssBounds = abyss.getGlobalBounds();

		if (abyssBounds.intersects(character.getGlobalBounds()))
		{
			this->deathCounter++;
			this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
			this->timeStart = clock();
			this->currentLevel = 0;
			this -> levelUpdate = true;
			this->currentLevelText.setString("Level: " + to_string(this->currentLevel+1));
			character.setPosition(65.f, 825.f);
		}

	}
	//enemy collision
	for (auto& movingEnemy : movingEnemys)
	{
		sf::FloatRect movingEnemyBounds = movingEnemy.getGlobalBounds();
		if (movingEnemyBounds.intersects(character.getGlobalBounds()))
		{
			this->deathCounter++;
			this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
			this->timeStart = clock();
			this->currentLevel = 0;
			this->levelUpdate = true;
			this->currentLevelText.setString("Level: " + to_string(this->currentLevel+1));
			character.setPosition(65.f, 825.f);
		}
	}
	//spike trap collision
	for (auto& spikeTrap : spikeTraps)
	{
		sf::FloatRect spikeTrapBounds = spikeTrap.spikeTrap.getGlobalBounds();

		if (spikeTrapBounds.intersects(character.getGlobalBounds()))
		{
			this->deathCounter++;
			this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
			this->timeStart = clock();
			this->currentLevel = 0;
			this->levelUpdate = true;
			this->currentLevelText.setString("Level: " + to_string(this->currentLevel+1));
			character.setPosition(65.f, 825.f);
		}
	}
	
	//end of level doors collision
	sf::FloatRect doorBounds = endOfLevel.getGlobalBounds();
	if (doorBounds.intersects(character.getGlobalBounds()))
	{
		this->currentLevel++;
		this->currentLevelText.setString("Level: " + to_string(this->currentLevel+1));
		this->levelUpdate = true;

	}

	//coin collision
	for (size_t i = 0; i < coins.size(); i++)
	{
		if (coins[i].getCoinGlobalBounds().intersects(character.getGlobalBounds()))
		{
			this->coinPickUpSound.play();
			coins[i].setIsCollected();
			this->totalCoins++;
			this->totalCoinsText.setString("Coins: " + to_string(this->totalCoins));
			coins.erase(coins.begin() + i);
		}
	}

	character.move(velocity);
	this->velocity.x = 0.0f;
	//screen collision
	if (character.getPosition().x < 0.f)
	{
		character.setPosition(0.f, character.getPosition().y); 
	}
	if (character.getPosition().y < 0.f)
	{
		character.setPosition(character.getPosition().x, 0.f); 
	}
	if (character.getPosition().x + character.getGlobalBounds().width > this->window_width) 
	{
		character.setPosition(this->window_width - character.getGlobalBounds().width, character.getPosition().y);
	}
	if (character.getPosition().y + character.getGlobalBounds().height > this->window_height)
	{
		character.setPosition(character.getPosition().x, this->window_height - character.getGlobalBounds().height);
		this->canJump = true;
	}
}

void Game::moveEnemy()
{
	for (auto& movingEnemy : movingEnemys)
	{

		if (movingEnemy.getPosition().x < enemyMoveRangeRight + enemyStartPositionX && moveRight)
		{
			movingEnemy.move(5, 0);
			this->movingEnemyTexture.loadFromFile("Images/cavemanL.png");
		}
		else
		{
			moveRight = false;
			movingEnemy.move(-5, 0);
			this->movingEnemyTexture.loadFromFile("Images/cavemanR.png");
		}
		if (movingEnemy.getPosition().x < enemyStartPositionX - enemyMoveRangeLeft)
			moveRight = true;

		if (movingEnemy.getPosition().x < 0.f)
		{
			movingEnemy.setPosition(0.f, movingEnemy.getPosition().y);
		}
		if (movingEnemy.getPosition().y < 0.f)
		{
			movingEnemy.setPosition(movingEnemy.getPosition().x, 0.f);
		}
		if (movingEnemy.getPosition().x + movingEnemy.getGlobalBounds().width > this->window_width)
		{
			movingEnemy.setPosition(this->window_width - movingEnemy.getGlobalBounds().width, movingEnemy.getPosition().y);
		}
		if (movingEnemy.getPosition().y + movingEnemy.getGlobalBounds().height > this->window_height)
		{
			movingEnemy.setPosition(movingEnemy.getPosition().x, this->window_height - movingEnemy.getGlobalBounds().height);
		}

	}
}

void Game::moveSpikeTrap()
{
	if (this->spikeTrapTimer < 50)
		this->spikeTrapTimer++;
	else
	{
		for (auto& spikeTrap : spikeTraps)
		{
			if (spikeTrap.spikeTrap.getPosition().y > spikeTrap.getStartPositionY() - spikeTrap.getMoveRange() && this->moveUp)
			{
				this->spikeTrapSound.play();
				spikeTrap.spikeTrap.move(0.f, -5.f);
			}
			else 
			{
				if (spikeTrap.spikeTrap.getPosition().y == spikeTrap.getStartPositionY())
				{
					spikeTrapTimer = 0;
					moveUp = true;
					break;
				}
				moveUp = false;
				spikeTrap.spikeTrap.move(0.f, 0.5f);
			}
		}
	}
}

void menuHighScore::loadHighScores()
{
	ifstream highScoreFile;
	highScoreFile.open("Saves/highscore.txt");
	string deaths;
	string time;
	string best;
	while (!highScoreFile.eof())
	{
		highScoreFile>>deaths>>time>>best;
	
		result x(deaths,time,best);
		Results.push_back(x);

	}
	highScoreFile.close();
	sort(Results.begin(), Results.end());
	font.loadFromFile("Fonts/arial.ttf");
	if (!this->font.loadFromFile("Fonts/arial.ttf"))
	{
		cout << "Error initFont";
	}
	string p;
	int y = 0;
	for (auto& i : Results)
	{
		y = y + 50;
		p = i.getDeaths() + "			" + "		" + i.getTime() + "			" + i.getBest();
		this->highScoreText.setFont(font);
		this->highScoreText.setCharacterSize(40);
		this->highScoreText.setStyle(sf::Text::Bold);
		this->highScoreText.setPosition(700, 200+y);
		this->highScoreText.setString(p);
		texts.push_back(this->highScoreText);
	}
	
}

void menuHighScore::showHighScores()
{
	for (auto& i : texts)
	{
		this->windowMenuHighScore.draw(i);
	}
}