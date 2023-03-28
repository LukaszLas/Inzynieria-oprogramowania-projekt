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

void Game::initObjects()
{

	createPlatform(100, 20, 250, 850);
	createPlatform(100, 20, 370, 700);
	createPlatform(100, 20, 50, 950);

	this->abyss.setFillColor(sf::Color::Red);
	this->abyss.setSize(sf::Vector2f(200.f, 10.f));
	this->abyss.setPosition(150.f, 1070.f);
	this->abysses.push_back(this->abyss);
}                              

void Game::initTexture()
{
	if (!this->texture.loadFromFile("Images/image.png"))
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
}

//void Game::initFont()
//{
//	if (!this->font.loadFromFile("Fonts/arial.ttf"))
//	{
//		cout << "Error initFont";
//	}
//}

//void Game::initText()
//{
//	this->text.setFont(font);
//	this->text.setString("Deaths: ");
//	this->text.setCharacterSize(50);
//	this->text.setStyle(sf::Text::Bold);
//	this->text.setPosition(1800.f, 1050.f);
//
//}


//Constructors /Destructor
Game::Game()
{
	this->initVariable();
	this->initWindow();
	this->initCharacter();
	//this->initTestingGround();
	this->initObjects();
	//this->initFont();
	//this->initText();
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
	//this->window->draw(this->text);
	for (auto& i : this->abysses)
	{
		this->window->draw(i);
	}
	for (auto& i : this->platforms)
	{
		this->window->draw(i);
	}

	this->window->display();
}




void Game::moveCharacter()
{
	//Key pressed move
	this->character.setSize(sf::Vector2f(50.f, 50.f));
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->character.setSize(sf::Vector2f(50.f, 35.f));
	}
	this->velocity.y += gravity * dt;


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
				character.setPosition(65.f, 825.f);
			}
			//right collision
			else if (characterBounds.left < abyssBounds.left
				&& characterBounds.left + characterBounds.width < abyssBounds.left + abyssBounds.width
				&& characterBounds.top < abyssBounds.top + abyssBounds.height
				&& characterBounds.top + characterBounds.height > abyssBounds.top)
			{
				character.setPosition(65.f, 825.f);
			}
			//left collision
			else if (characterBounds.left > abyssBounds.left
				&& characterBounds.left + characterBounds.width > abyssBounds.left + abyssBounds.width
				&& characterBounds.top < abyssBounds.top + abyssBounds.height
				&& characterBounds.top + characterBounds.height > abyssBounds.top)
			{
				character.setPosition(65.f, 825.f);
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
