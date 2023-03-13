#include <iostream>
#include "Game.h"
int main()
{
	//init game
	Game game;

	while (game.getWindowIsOpen())
	{
		//Update
		game.update();

		//Render
		game.render();
	}
	return 0;
}
/*
		sf::RectangleShape rs(sf::Vector2f(100, 100));
		rs.setPosition(400, 400);
		window.clear(sf::Color::Black);
		window.draw(rs);
		window.display();
		while (window.pollEvent(ev))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				rs.move(-10.f,0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				rs.move(10.f, 0);
			}
			if (e.type == sf::Event::Closed)
				window.close();
		}*/
