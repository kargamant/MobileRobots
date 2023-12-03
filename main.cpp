#include "Application.h"
#include <iostream>

int main()
{
	Game::Application app = Game::Application(10, 10);
	app.getField().consoleOutField();
	std::cout << std::endl;

	app.getAi().consoleOutGraph(std::cout);
	//app.sandBox();
	return 0;
}