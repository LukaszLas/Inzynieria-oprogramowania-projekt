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

			Game game;
			while (game.getWindowIsOpen())
			{
				//Update
				game.update();

				//Render
				game.render();
				//std::cout << "Mem allocated: " << memoryAllocated << endl;
			}

	

	//std::cout << "Mem allocated: " << memoryAllocated;
	return 0;



}
