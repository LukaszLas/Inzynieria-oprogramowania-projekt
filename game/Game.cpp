#include "Game.h"

//Private Functions
void Game::initVariable()
{
	this->window = nullptr;
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	const float window_width = 800;
	const float window_height = 600;

}

void Game::initWindow()
{
	this->videoMode.height = window_height;
	this->videoMode.width = window_width;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initCharacter()
{
	this->character.setPosition(400, 450);
	this->character.setSize(sf::Vector2f(50.f, 50.f));
	this->character.setFillColor(sf::Color::White);
}

void Game::initTestingGround()
{
	this->testing_ground.setPosition(0,window_height-groundHeight);
	this->testing_ground.setSize(sf::Vector2f(window_width, groundHeight));
	this->testing_ground.setFillColor(sf::Color::Green);
}

void Game::initObjects()
{
	this->platform.setFillColor(sf::Color::Red);
	this->platform.setSize(sf::Vector2f(100.f, 20.f));
	this->platform.setPosition(300.f, 350.f);
	this->platforms.push_back(this->platform);
}

//Constructors /Destructor
Game::Game()
{
	this->initVariable();
	this->initWindow();
	this->initCharacter();
	this->initTestingGround();
	this->initObjects();
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
	this->window->draw(this->testing_ground);
	for (auto& i : this->platforms)
	{
		this->window->draw(i);
	}
	this->window->display();
}




void Game::moveCharacter()
{
	float gravity = 300.0f;
	float jumpHeight = 300.0f;
	//Key pressed move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->velocity.x -= moveSpeed*this->getDT();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->velocity.x += moveSpeed*this->getDT();
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (this->canJump==true))
	{
		this->canJump = false;
		this->velocity.y = -sqrt(2.0f * gravity * jumpHeight);
	}

	this->velocity.y += gravity * dt;


	//objects collision
	for (auto &platform : platforms)
	{
		sf::FloatRect characterBounds = character.getGlobalBounds();
		sf::FloatRect platformBounds = platform.getGlobalBounds();
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

	character.move(velocity);
	this->velocity.y = 0.0f;
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






