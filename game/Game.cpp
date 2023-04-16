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
	this->enemyMoveRangeRight = 400;
	this->enemyMoveRangeLeft = 400;
	this->enemyStartPositionX = this->movingEnemy.getPosition().x;
	movingEnemys.push_back(this->movingEnemy);
	//createMovingEnemies(200, 200, 100, 100);
}
void Game::createMovingEnemies(float positionX, float positionY, float moveRangeRight, float moveRangeLeft)
{
	this->movingEnemy.setPosition(positionX, positionY);
	this->initTexture();
	this->initSprite();
	this->movingEnemy.setSize(sf::Vector2f(60.f, 60.f));
	this->movingEnemy.setTexture(&movingEnemyTexture);
	this->enemyMoveRangeRight = moveRangeRight;
	this->enemyMoveRangeLeft = moveRangeLeft;
	this->enemyStartPositionX = this->movingEnemy.getPosition().x;
	movingEnemys.push_back(this->movingEnemy);
}
void Game::initObjects()
{

	createPlatform(100, 20, 250, 850);
	createPlatform(100, 20, 370, 700);
	createPlatform(100, 20, 50, 950);

	//this->abyss.setFillColor(sf::Color::Red);
	this->abyss.setSize(sf::Vector2f(200.f, 9.f));
	this->abyss.setPosition(150.f, 1070.f);
	this->abyss.setTexture(&abyssTexture);
	this->abysses.push_back(this->abyss);

	
	//this->spikeTrap.setFillColor(sf::Color::Magenta);
	this->spikeTrap.setSize(sf::Vector2f(30.f, 19.f));
	this->spikeTrap.setPosition(400.f, 700.f);
	this->spikeTrap.setTexture(&spikesTexture);
	this->spikeTraps.push_back(this->spikeTrap);
	startingpos = spikeTrap.getPosition().y;
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
}

void Game::createPlatform(float sizeX, float sizeY, float positionX, float positionY)
{
	this->platform.setSize(sf::Vector2f(sizeX, sizeY));
	this->platform.setPosition(positionX, positionY);
	this->platform.setTexture(&platformTexture);
	this->platforms.push_back(this->platform);
}

void Game::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->enemySprite.setTexture(this->movingEnemyTexture);
	this->platformSprite.setTexture(this->platformTexture);
	this->abyssSprite.setTexture(this->abyssTexture);
	this->spikesSprite.setTexture(this->spikesTexture);
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
}

void Game::initTimerText()
{
	this->TimerText.setFont(font);
	this->TimerText.setCharacterSize(30);
	this->TimerText.setStyle(sf::Text::Bold);
	this->TimerText.setPosition(20.f, 40.f);
	

}
//Constructors /Destructor
Game::Game()
{
	this->initVariable();
	this->initWindow();
	this->initCharacter();
	this->initEnemies();
	this->initObjects();
	this->initFont();
	this->initText();
	this->initTimerText();
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
				this->window->close();
			break;
		}
	}
}

void Game::render()
{
	this->window->clear();
	//draw game objects
	this->window->draw(this->character);
	this->window->draw(this->movingEnemy);
	for (auto& i : this->spikeTraps)
	{
		this->window->draw(i);
	}
	for (auto& i : this->abysses)
	{
		this->window->draw(i);
	}
	for (auto& i : this->platforms)
	{
		this->window->draw(i);
	}
	for (auto& i : this->movingEnemys)
	{
		this->window->draw(i);
	}
	//draw UI
	this->window->draw(this->deathCounterText);
	this->window->draw(this->TimerText);

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
	for (auto& abyss : abysses)
	{
		sf::FloatRect abyssBounds = abyss.getGlobalBounds();

		if (abyssBounds.intersects(nextPos))
		{
			this->deathCounter++;
			this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
			this->timeStart = clock();
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
			character.setPosition(65.f, 825.f);
		}
	}
	//spike trap collision
	for (auto& spikeTrap : spikeTraps)
	{
		sf::FloatRect spikeTrapBounds = spikeTrap.getGlobalBounds();

		if (spikeTrapBounds.intersects(character.getGlobalBounds()))
		{
			this->deathCounter++;
			this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
			this->timeStart = clock();
			character.setPosition(65.f, 825.f);
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
			if (spikeTrap.getPosition().y > startingpos - spikeTrapMoveRange && this->moveUp)
			{
				spikeTrap.move(0.f, -5.f);
			}
			else 
			{
				if (spikeTrap.getPosition().y == startingpos)
				{
					spikeTrapTimer = 0;
					moveUp = true;
					break;
				}
				moveUp = false;
				spikeTrap.move(0.f, 0.5f);
			}
		}
	}
}
