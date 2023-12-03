#include "Application.h"
#include <iostream>

int main()
{
	Game::Application app = Game::Application(10, 10);
	app.getField().consoleOutField();
	std::cout << std::endl;
	Field::Cell& cell1 = app.getField().getCellByCoordinates(0, 0);
	Field::Cell& cell2 = app.getField().getCellByCoordinates(1, 1);
	std::vector<Robots::Node*> path = app.getAi().path(&cell1, &cell2, app.getField());
	for (Robots::Node* node : path)
	{
		node->consoleOut(std::cout);
	}
	//app.getAi().consoleOutGraph(std::cout);
	//app.sandBox();
	return 0;
}