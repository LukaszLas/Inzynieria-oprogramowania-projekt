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
	this->movingEnemy.setPosition(enemyStartPositionX,enemyStartPositionY);
	this->initTexture();
	this->initSprite();
	this->movingEnemy.setSize(sf::Vector2f(60.f, 60.f));
	this->movingEnemy.setTexture(&movingEnemyTexture);
	float enemyMoveRangeRight = 50;
	float enemyMoveRangeLeft = 50;
}
void Game::initObjects()
{

	createPlatform(100, 20, 250, 850);
	createPlatform(100, 20, 370, 700);
	createPlatform(100, 20, 50, 950);

	this->abyss.setFillColor(sf::Color::Red);
	this->abyss.setSize(sf::Vector2f(200.f, 9.f));
	this->abyss.setPosition(150.f, 1070.f);
	this->abysses.push_back(this->abyss);

	
	this->spikeTrap.setFillColor(sf::Color::Magenta);
	this->spikeTrap.setSize(sf::Vector2f(30.f, 19.f));
	this->spikeTrap.setPosition(400.f, 700.f);
	this->spikeTraps.push_back(this->spikeTrap);
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
}

void Game::createPlatform(float sizeX, float sizeY, float positionX, float positionY)
{
	this->platform.setFillColor(sf::Color::Green);
	this->platform.setSize(sf::Vector2f(sizeX, sizeY));
	this->platform.setPosition(positionX, positionY);
	this->platforms.push_back(this->platform);
}

void Game::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->enemySprite.setTexture(this->movingEnemyTexture);
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
	this->deathCounterText.setPosition(1750.f, 1025.f);
	this->deathCounterText.setString("Deaths: 0");
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

	//draw UI
	this->window->draw(this->deathCounterText);

	this->window->display();
}




void Game::moveCharacter()
{
	//Key pressed move
	this->character.setSize(sf::Vector2f(50.f, 50.f));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->velocity.x -= moveSpeed*this->getDT();
		this->characterRightGoing = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->velocity.x += moveSpeed*this->getDT();
		this->characterRightGoing = true;

	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (this->canJump==true))
	{
		this->canJump = false;
		this->velocity.y = -sqrt(2.0f * gravity * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->character.setSize(sf::Vector2f(50.f, 35.f));
	}
	this->velocity.y += gravity * dt;

	if(this->characterRightGoing)
		this->texture.loadFromFile("Images/image.png");
	else
		this->texture.loadFromFile("Images/imageL.png");

	//objects collision
	for (auto &platform : platforms)
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
		sf::FloatRect characterBounds = character.getGlobalBounds();
		sf::FloatRect abyssBounds = abyss.getGlobalBounds();

		if (abyssBounds.intersects(nextPos))
		{
			//abyss bottom collision
			if (characterBounds.top < abyssBounds.top
				&& characterBounds.top + characterBounds.height < abyssBounds.top + abyssBounds.height
				&& characterBounds.left < abyssBounds.left + abyssBounds.width
				&& characterBounds.left + characterBounds.width > abyssBounds.left)
			{
				this->deathCounter++;
				this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
				character.setPosition(65.f, 825.f);
			}
			//right collision
			else if (characterBounds.left < abyssBounds.left
				&& characterBounds.left + characterBounds.width < abyssBounds.left + abyssBounds.width
				&& characterBounds.top < abyssBounds.top + abyssBounds.height
				&& characterBounds.top + characterBounds.height > abyssBounds.top)
			{
				this->deathCounter++;
				this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
				character.setPosition(65.f, 825.f);
			}
			//left collision
			else if (characterBounds.left > abyssBounds.left
				&& characterBounds.left + characterBounds.width > abyssBounds.left + abyssBounds.width
				&& characterBounds.top < abyssBounds.top + abyssBounds.height
				&& characterBounds.top + characterBounds.height > abyssBounds.top)
			{
				this->deathCounter++;
				this->deathCounterText.setString("Deaths: " + to_string(this->deathCounter));
				character.setPosition(65.f, 825.f);
			}
		}

	}
	//enemy collision
	sf::FloatRect movingEnemyBounds = movingEnemy.getGlobalBounds();
	if (movingEnemyBounds.intersects(this->character.getGlobalBounds()))
	{
		character.setPosition(65.f, 825.f);
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

void Game::moveSpikeTrap()
{
	if (this->spikeTrapTimer < 50)
		this->spikeTrapTimer++;
	else
	{
		for (auto& spikeTrap : spikeTraps)
		{
			float startingPos = spikeTrap.getPosition().y;
			if (spikeTrap.getPosition().y < startingPos + spikeTrapMoveRange)
			{
				spikeTrap.move(0.f, -5.f);
			}
			else if (spikeTrap.getPosition().y >= startingPos + spikeTrapMoveRange)
			{
				spikeTrap.move(0.f, 2.f);
				if (startingPos = spikeTrap.getPosition().y)
				{
					this->spikeTrapTimer = 0;
				}
			}
		}
	}
}
