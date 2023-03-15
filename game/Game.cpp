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

//Constructors /Destructor
Game::Game()
{
	this->initVariable();
	this->initWindow();
	this->initCharacter();
	this->initTestingGround();
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
	this->window->display();
}

void Game::moveCharacter()
{
	velocity.x = 0.0f;
	velocity.y = 2.0f;
	//Key pressed move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->velocity.x -= moveSpeed*this->getDT();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->velocity.x += moveSpeed*this->getDT();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y += -moveSpeed * 2 * velocity.y * dt;
	}
	character.move(velocity);
	//collisions
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
	}
}



