#include "Application.h"
#include <iostream>
#include "Platforms/KamikazeRobot.h"

int main()
{
	Field::Field::GROUND_MODE_ON = true;
	Game::Application app = Game::Application(5, 5);

	for (int i = 0; i < 5; i++)
	{
		//if (i == 2) continue;
		Robots::KamikazeRobot kr = Robots::KamikazeRobot();
		if (i == 1 || i==3) kr.setCoordinates(i, 3);
		else kr.setCoordinates(i, 1);
		app.getField().placePlatform(&kr);
		app.getAi().getGraph()[kr.getCoordinates()].isTraversable = false;
	}
	

	app.getField().consoleOutField();
	std::cout << std::endl;
	Field::Cell& cell1 = app.getField().getCellByCoordinates(1, 4);
	Field::Cell& cell2 = app.getField().getCellByCoordinates(0, 0);
	std::vector<Robots::Node*> path = app.getAi().path(&cell1, &cell2, app.getField());
	for (Robots::Node* node : path)
	{
		node->consoleOut(std::cout);
	}
	return 0;
}