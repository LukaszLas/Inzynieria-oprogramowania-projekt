#include <iostream>
#include "Game.h"
using namespace sf;
#if _DEBUG
static size_t memoryAllocated = 0;

void* operator new (size_t size)
{
	memoryAllocated += size;
	return malloc(size);
}

void operator delete (void* ptr, size_t size)
{
	memoryAllocated -= size;
	free(ptr);
}
#endif

int main()
{
	string select;
	sf::RenderWindow menu(sf::VideoMode(1920,1080),"menu", sf::Style::Fullscreen);
	Font font;
	font.loadFromFile("Fonts/arial.ttf");
	bool menuVisible = true;
	Text startGameText("Start Game", font, 40);
	Text highScoreText("High Score", font, 40);
	Text exitText("Exit", font, 40);
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Images/menu.png");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0); 
	backgroundSprite.setScale(1.0f, 1.0f);
	startGameText.setPosition(300, 200);
	highScoreText.setPosition(300, 250);
	exitText.setPosition(300, 300);
	while (menu.isOpen())
	{
		Event event;
		while (menu.pollEvent(event))
		{
			if (event.type == Event::Closed)
				menu.close();
			else if (event.type == Event::MouseButtonPressed)
			{
				Vector2i mousePosition = Mouse::getPosition(menu);
				if (startGameText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					menuVisible = false;
					select = "game";
					menu.close();

				}
				else if (highScoreText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					menuVisible = false;
					select = "highscore";
					menu.close();
				}
				else if (exitText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					menu.close();
				}

			}
		}
		
		if (menuVisible)
		{
			menu.draw(backgroundSprite);
			menu.draw(startGameText);
			menu.draw(highScoreText);
			menu.draw(exitText);
		}
		else if (select=="game")
		{
			Game game;
			while (game.getWindowIsOpen())
			{
				if (select == "highscore")
					game.setCurrentLevel(-1);
				//Update
				game.update();

				//Render
				game.render();
				//std::cout << "Mem allocated: " << memoryAllocated << endl;
			}
			 menu.create(sf::VideoMode(1920, 1080), "menu", sf::Style::Fullscreen);
			 menu.draw(backgroundSprite);
			 menu.draw(startGameText);
			 menu.draw(highScoreText);
			 menu.draw(exitText);
		}
		else if (select=="highscore")
		{
			menuHighScore obj;
			obj.run();
			menuVisible = true;
			menu.create(sf::VideoMode(1920, 1080), "menu", sf::Style::Fullscreen);
			menu.draw(backgroundSprite);
			menu.draw(startGameText);
			menu.draw(highScoreText);
			menu.draw(exitText);
		}
		menuVisible = true;

		menu.display();
		
	}
	

	
	
	//init game

	//std::cout << "Mem allocated: " << memoryAllocated;
	return 0;



}
