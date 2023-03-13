#include "Game.h"

//Private Functions
void Game::initVariable()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

}

void Game::initCharacter()
{
	this->character.setPosition(400, 400);
	this->character.setSize(sf::Vector2f(100.f, 100.f));
	this->character.setFillColor(sf::Color::White);
	//this->jumpHeight = jumpHeight;
	//this->speed = speed;
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
	//velocity.x = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->character.move(-10.f, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->character.move(10.f, 0);
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
