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
