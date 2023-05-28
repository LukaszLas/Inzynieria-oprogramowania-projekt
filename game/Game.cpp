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

void Game::initCoins()
{
	// lvl 1
	createCoin(20, 1350, 330, 1);
	createCoin(20, 1350, 380, 1);
	createCoin(20, 570, 500, 1);
	createCoin(20, 280, 800, 1);
	createCoin(20, 1775, 1025, 1);
	// lvl 2
	createCoin(20, 1890, 880, 0);
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
	srand(time(NULL));
	switch (this->currentLevel)
	{
	case -1:                                     ///shop
		platforms.clear();
		abysses.clear();
		spikeTraps.clear();
		movingEnemys.clear();
		createPlatform(1920, 7, 0, 1073);
		createEndOfLevel(50, 100, 1870, 3000);
		createShop(125, 80, 250, 3000);
		createShopDoor(50, 100, 350, 980);
		spawnMerchant(50, 80, 1520, 993);
		createPlatform(300, 20, this->window_width/6, 910);
		createPlatform(300, 20, 4*(this->window_width/6), 910);
		createPlatform(300, 20, 800, 760);
		createPlatform(300, 20, this->window_width/6, 610);
		createPlatform(300, 20, 4*(this->window_width/6), 610);
		if (rollDialogue == 1)
		{
			this->dialogueText.setPosition(1475.f, 970.f);
			this->dialogueText.setString("Welcome to my shop!");
			createChatBox(150, 30, 1470, 970);
		}
		else if (rollDialogue == 2)
		{
			this->dialogueText.setPosition(1485.f, 970.f);
			this->dialogueText.setString("Hello adventurer!");
			createChatBox(130, 30, 1480, 970);
		}
		else if (rollDialogue == 3)
		{
			this->dialogueText.setPosition(1445.f, 970.f);
			this->dialogueText.setString("Hope you brought some coins!");
			createChatBox(210, 30, 1440, 970);
		}
		for (int i = 0; i < coins.size(); i++)
		{
			coins[i].setIsVisible(0);
		}
		break;
	case 0:
		platforms.clear();
		abysses.clear();
		spikeTraps.clear();
		movingEnemys.clear();
		createPlatform(100, 20, 250, 850);
		createPlatform(100, 20, 370, 700);
		createPlatform(100, 20, 50, 950);
		createPlatform(1920, 7, 0, 1073);
		createPlatform(150, 20, 520, 550);
		createPlatform(100, 20, 750, 425);
		createPlatform(25, 20, 550, 300);
		createPlatform(100, 20, 1000, 425);
		createPlatform(40, 20, 1350, 425);
		createPlatform(200, 20, 250, 205);
		createSpikeTrap(30, 400, 700);
		createSpikeTrap(30, 450, 700);
		createMovingEnemies(1350, 1020, 160, 160);
		createAbyss(100, 11, 650, 1070,"lava");
		createAbyss(100,11, 830, 1070,"lava");
		createAbyss(380, 19, 650, 800,"abyss");
		createAbyss(420, 11, 150, 1070,"lava");
		createAbyss(310, 19, 1070, 500,"abyss");
		createShop(125, 80, 250, 125);
		createEndOfLevel(50, 100, 1870, 980);
		createShopDoor(50, 100, 50, 3000);
		spawnMerchant(50, 80, 1820, 3000);
		createChatBox(100, 20, 1495, 3000);
		this->dialogueText.setPosition(1500.f, 3000.f);
		for (int i = 0; i < 5; i++)
		{
			coins[i].setIsVisible(1);
		}
		for (size_t i = 5; i < coins.size(); i++)
		{
			coins[i].setIsVisible(0);
		}
		break;
	case 1:
		platforms.clear();
		abysses.clear();
		spikeTraps.clear();
		movingEnemys.clear();
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
		createAbyss(1680, 11, 0, 1070,"lava");
		createShopDoor(50, 100, 50, 3000);
		createShop(125, 80, 250, 3000);
		createEndOfLevel(50, 100, 400, 200);
		spawnMerchant(50, 80, 1820, 3000);
		createChatBox(100, 20, 1495, 3000);
		this->dialogueText.setPosition(1500.f, 3000.f);
		for (int i = 0; i < 5; i++)
		{
			coins[i].setIsVisible(0);
		}
		for (size_t i = 5; i < coins.size(); i++)
		{
			coins[i].setIsVisible(1);
		}
		break;
	case 2:
		platforms.clear();
		abysses.clear();
		spikeTraps.clear();
		movingEnemys.clear();
		coins.clear();
		createShopDoor(50, 100, 50, 3000);
		createShop(125, 80, 250, 3000);
		createEndOfLevel(50, 100, 400, 2200);
		createEndOfGame(50, 100, 1030, 800);
		spawnMerchant(50, 80, 1820, 3000);
		createChatBox(100, 20, 1495, 3000);
		this->dialogueText.setPosition(1500.f, 3000.f);
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

void Game::createAbyss(float sizeX, float sizeY, float positionX, float positionY, string typeTexture)
{
	this->abyss.setSize(sf::Vector2f(sizeX, sizeY));
	this->abyss.setPosition(positionX, positionY);
	if (typeTexture == "abyss")
		this->abyss.setTexture(&abyssTexture);
	else
		this->abyss.setTexture(&lavaTexture);

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

void Game::createShopDoor(float sizeX, float sizeY, float positionX, float positionY)
{
	this->shopDoor.setSize(sf::Vector2f(sizeX, sizeY));
	this->shopDoor.setTexture(&endOfLevelTexture);
	this->shopDoor.setPosition(positionX, positionY);
}

void Game::createCoin(float radius, float positionX, float positionY, int visibility)
{
		classCoin coin;
		coin.setCoinRadius(radius);
		coin.setCoinPosition(positionX, positionY);
		coin.setCoinTexture(coinTexture);
		coin.setIsVisible(visibility);
		coins.push_back(coin);
}

void Game::createShop(float sizeX, float sizeY, float positionX, float positionY)
{
	this->shop.setSize(sf::Vector2f(sizeX, sizeY));
	this->shop.setTexture(&shopTexture);
	this->shop.setPosition(positionX, positionY);
}

void Game::spawnMerchant(float sizeX, float sizeY, float positionX, float positionY)
{
	this->merchant.setSize(sf::Vector2f(sizeX, sizeY));
	this->merchant.setTexture(&merchantTexture);
	this->merchant.setPosition(positionX, positionY);
}

void Game::createChatBox(float sizeX, float sizeY, float positionX, float positionY)
{
	this->chatBox.setSize(sf::Vector2f(sizeX, sizeY));
	this->chatBox.setPosition(positionX, positionY);
	this->chatBox.setFillColor(sf::Color(0, 0, 0, 64));

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
	if (!this->shopDoorTexture.loadFromFile("Images/door.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->lavaTexture.loadFromFile("Images/lava.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->shopTexture.loadFromFile("Images/shop.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->merchantTexture.loadFromFile("Images/merchant.png"))
	{
		cout << "Error initTexture";
	}
	if (!this->itemTexture_1.loadFromFile("Images/placeholder.png"))
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
	this->lavaSprite.setTexture(this->lavaTexture);
	this->shopSprite.setTexture(this->shopTexture);
	this->shopDoorSprite.setTexture(this->endOfLevelTexture);
	this->merchantSprite.setTexture(this->merchantTexture);
	this->itemSprite_1.setTexture(this->itemTexture_1);
}

void Game::initFont()
{
	if (!this->UIfont.loadFromFile("Fonts/arial.ttf"))
	{
		cout << "Error initFont";
	}
	if (!this->dialogueFont.loadFromFile("Fonts/indiestarbb_reg.ttf"))
	{
		cout << "Error initFont";
	}
}

void Game::initText()
{
	this->deathCounterText.setFont(UIfont);
	this->deathCounterText.setCharacterSize(30);
	this->deathCounterText.setStyle(sf::Text::Bold);
	this->deathCounterText.setPosition(20.f, 80.f);
	this->deathCounterText.setString("Deaths: 0");

	this->currentLevelText.setFont(UIfont);
	this->currentLevelText.setCharacterSize(30);
	this->currentLevelText.setStyle(sf::Text::Bold);
	this->currentLevelText.setPosition(1750.f, 40.f);
	this->currentLevelText.setString("Level: 1");

	this->totalCoinsText.setFont(UIfont);
	this->totalCoinsText.setCharacterSize(30);
	this->totalCoinsText.setStyle(sf::Text::Bold);
	this->totalCoinsText.setPosition(1750.f, 80.f);
	this->totalCoinsText.setString("Coins: " + to_string(this->totalCoins));

	this->dialogueText.setFont(dialogueFont);
	this->dialogueText.setCharacterSize(20);
	this->dialogueText.setStyle(sf::Text::Bold);
	this->dialogueText.setFillColor(sf::Color::Red);
}

void Game::initTimerText()
{
	this->TimerText.setFont(UIfont);
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

 string Game::getAsString()
{
	clock_t timeStop = clock();
	float currentTIME = static_cast<float>(timeStop - timeStart) / CLOCKS_PER_SEC;
	stringstream ss;


	ss << this->character.getPosition().x << " " << this->character.getPosition().y << " "
		<< this->currentLevel << " " << this->totalCoins << " " << currentTIME << " "
		<< this->coins.size() << " ";
	for (size_t i = 0; i < coins.size(); i++)
	{
		 ss << this->coins[i].getIsCollected() << " " << this->coins[i].getIsVisible() << " ";
	}
	cout << ss.str();
	return ss.str();
}

void Game::saveGame()
{
	if (this->deathCounter==0)
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
}

void Game::loadGame()
{
	/*
		wczytanie danych:
		this->timeStart;
		this->totalTime;
	
	*/
	this->gameLoad.open("Saves/gamesave.txt");
	if (this->gameLoad.is_open())
	{
		sf::Vector2f position;
		int level=0, coins=0;
		float currentTIME;

		this->gameLoad >> position.x >> position.y >> level >> coins >> currentTIME;

		this->character.setPosition(position);
		this->currentLevel = level;
		this->totalCoins = coins;
		this->deathCounter = 0;
		this->timeStart = currentTIME;
		this->totalTime = currentTIME;

		this->initObjects();
		this->initText();
		this->render();
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
	this->initCoins();
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
	shopTimerFun();
	merchantAnimation();
	clock_t timeStop = clock();
	duration = static_cast<float>(timeStop - timeStart) / CLOCKS_PER_SEC;
	TimerText.setString(to_string(duration));
	//end of game collision
	sf::FloatRect endOfGameBounds = endOfGame.getGlobalBounds();
	if (endOfGameBounds.intersects(character.getGlobalBounds())&&gameEnded==false)
	{
		highscorefile.open("Saves/highscore.txt", ofstream::app);
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
				this->window->close();
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
	this->window->draw(this->shop);
	this->window->draw(this->shopDoor);
	this->window->draw(this->merchant);
	this->window->draw(this->chatBox);
	this->window->draw(this->dialogueText);
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
		if(!(this->coins[i].getIsCollected()) && this->coins[i].getIsVisible())
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
		if (coins[i].getCoinGlobalBounds().intersects(character.getGlobalBounds()) && !(coins[i].getIsCollected()) && coins[i].getIsVisible())
		{
			this->coinPickUpSound.play();
			coins[i].setIsCollected();
			coins[i].setIsVisible(0);
			this->totalCoins++;
			this->totalCoinsText.setString("Coins: " + to_string(this->totalCoins));
			//coins.erase(coins.begin() + i);
		}
	}

	//shop collision
	sf::FloatRect shopBounds = shop.getGlobalBounds();
	if (shopBounds.intersects(character.getGlobalBounds()) && this->ev.key.code == sf::Keyboard::Enter && this->leftShop == false)
	{
		this->rollDialogue = rand() % 3 + 1;
		this->saveCharacterPosX = character.getPosition().x;
		this->saveCharacterPosY = character.getPosition().y;
		this->saveCurrentLevel = this->currentLevel;
		this->currentLevel = -1;
		this->levelUpdate = true;
		this->character.setPosition(this->window_width/2, 1020.f);
	}

	//shop door collision
	sf::FloatRect shopDoorBounds = shopDoor.getGlobalBounds();
	if (shopDoorBounds.intersects(character.getGlobalBounds()) && this->ev.key.code == sf::Keyboard::Enter)
	{
		this->currentLevel = this->saveCurrentLevel;
		this->leftShop = true;
		this->levelUpdate = true;
		this->character.setPosition(saveCharacterPosX, saveCharacterPosY);

	}

	//shop items collision
	for (size_t itemID = 0; itemID < items.size(); itemID++)
	{
		if (items[itemID].getItemGlobalBounds().intersects(character.getGlobalBounds())
			&& !(items[itemID].getIsBought()) && items[itemID].getItemVisibility()
			&& this->totalCoins >= items[itemID].getItemPrice()
			&& this->ev.key.code == sf::Keyboard::Enter)
		{
			//this->itemPurchaseSound.play();
			items[itemID].setIsBought();
			items[itemID].setItemVisibility(0);
			this->totalCoins -= items[itemID].getItemPrice();
			this->totalCoinsText.setString("Coins: " + to_string(this->totalCoins));
			switch (itemID)
			{
			case 0:
				///efekty po kupieniu przedmiotu 0
				break;
			case 1:
				///efekty po kupieniu przedmiotu 1
				break;
			///...
			}
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

void Game::shopTimerFun()
{
	if (this->shopTimer < 300)
		this->shopTimer++;
	else
	{
		this->leftShop = false;
		this->shopTimer = 0;
	}
	
}

void Game::merchantAnimation()
{
	if (this->currentLevel == -1)
	{
		if (this->merchantTimer < 50)
			this->merchantTimer++;
		else
		{
			if (this->merchantAnim == false)
			{
				this->merchant.setSize(sf::Vector2f(50, 75));
				this->merchant.setPosition(1520.f, 998.f);
				this->merchantTimer = 0;
				this->merchantAnim = true;
			}
			else
			{
				this->merchant.setSize(sf::Vector2f(50, 80));
				this->merchant.setPosition(1520.f, 993.f);
				this->merchantTimer = 0;
				this->merchantAnim = false;
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
	float best;
	int max = 0;
	while (!highScoreFile.eof())
	{
		
		highScoreFile>>deaths>>time>>best;
		result x(deaths,time,round(best*1000)/1000);
		cout << x;
		Results.push_back(x);
		max++;
		if (max > 10)
			break;
	}
	highScoreFile.close();
	Results.pop_back();
	sort(Results.begin(), Results.end());
	UIfont.loadFromFile("Fonts/arial.ttf");
	cout << Results[0];
	if (!this->UIfont.loadFromFile("Fonts/arial.ttf"))
	{
		cout << "Error initFont";
	}
	string p,b;
	int y = 0;
	for (auto& i : Results)
	{
		y = y + 50;
		p = i.getDeaths();
		this->highScoreTextDeath.setFont(UIfont);
		this->highScoreTextDeath.setCharacterSize(40);
		this->highScoreTextDeath.setStyle(sf::Text::Bold);
		this->highScoreTextDeath.setPosition(700, 200+y);
		this->highScoreTextDeath.setString(p);
		textsDeath.push_back(this->highScoreTextDeath);
		p = i.getTime() ;
		this->highScoreTextTotal.setFont(UIfont);
		this->highScoreTextTotal.setCharacterSize(40);
		this->highScoreTextTotal.setStyle(sf::Text::Bold);
		this->highScoreTextTotal.setPosition(1200, 200 + y);
		this->highScoreTextTotal.setString(p);
		textsTotal.push_back(this->highScoreTextTotal);
		p = i.getBestStr();
		this->highScoreTextBest.setFont(UIfont);
		this->highScoreTextBest.setCharacterSize(40);
		this->highScoreTextBest.setStyle(sf::Text::Bold);
		this->highScoreTextBest.setPosition(900, 200 + y);
		this->highScoreTextBest.setString(p);
		textsBest.push_back(this->highScoreTextBest);
	}
	
}

void menuHighScore::showHighScores()
{
	for (auto& i : textsDeath)
	{
		this->windowMenuHighScore.draw(i);
	}
	for (auto& i : textsBest)
	{
		this->windowMenuHighScore.draw(i);
	}
	for (auto& i : textsTotal)
	{
		this->windowMenuHighScore.draw(i);
	}
}

void menuHighScore::initBackground()
{
	backgroundTexture.loadFromFile("Images/highscore.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
	backgroundSprite.setScale(1.0f, 1.0f);
	windowMenuHighScore.draw(backgroundSprite);
}