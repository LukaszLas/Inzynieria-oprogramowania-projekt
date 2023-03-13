#include "Game.h"

//Private Functions
void Game::initVariable()
{
	this->window = nullptr;
	sf::Vector2f velocity(sf::Vector2f(0, 0));
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	//this->window->setFramerateLimit(60);
}

void Game::initCharacter()
{
	this->character.setPosition(400, 450);
	this->character.setSize(sf::Vector2f(100.f, 100.f));
	this->character.setFillColor(sf::Color::White);
}

//Constructors /Destructor
Game::Game()
{
	this->initVariable();
	this->initWindow();
	this->initCharacter();
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
	this->pollEvents();
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
		moveCharacter();
	}
}

void Game::render()
{
	this->window->clear();
	//draw game objects
	this->window->draw(this->character);
	this->window->display();
}

void Game::moveCharacter()
{
	velocity.x = 0.0f;
	float dt = clock.restart().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->velocity.x -= this->moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->velocity.x += this->moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump)
	{
		canJump = false;
		this->velocity.y = -sqrtf(2.0f * 9.81f * jumpHeight);
		//this->velocity.y = this->jumpSpeed * dt *(-1);
		//this->character.move({ 0, -moveSpeed });
	}
	velocity.y += 9.81f * dt;
	
	this->character.move(velocity.x, velocity.y);
	if (this->character.getPosition().y + this->character.getSize().y< groundHeight || this->velocity.y<0)
	{
		this->velocity.y += this->gravity;
	}
	else
	{
		this->character.setPosition(this->character.getPosition().x, groundHeight);
		velocity.y = 0;
		canJump = true;
	}
	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump)
	//{
	//	canJump == false;
	//
		//velocity.y = sqrtf(2.0f * 981.0f * jumpHeight);
	//	
	//}
	//velocity.y += 981.0f;
}
