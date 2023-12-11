#include "Game/Application.h"
#include <iostream>
#include "Platforms/KamikazeRobot.h"
#include "Platforms/RobotCommander.h"
#include "Modules/Gun.h"
#include "Platforms/MobilePlatform.h"
#include "Modules/EnergyGenerator.h"
#include "Modules/Sensor.h"
#include "Platforms/RobotDestroyer.h"

int main()
{
	Field::Field::GROUND_MODE_ON = false;
	Field::Field::OBSTACLE_PERCENTAGE = 30;
	Game::Application app = Game::Application(7, 7);

	Robots::RobotCommander rc = Robots::RobotCommander();
	Robots::MobilePlatform mp = Robots::MobilePlatform();
	Robots::RobotDestroyer rd = Robots::RobotDestroyer();
	Robots::Sensor sens = Robots::Sensor();
	Robots::EnergyGenerator eg = Robots::EnergyGenerator();

	rd.setName("aboba");

	eg.connect(rd.getGun());
	rd.placeModule(sens);
	rd.placeModule(eg);
	rd.getGun().turnOn();

	eg.connect(rc.getCpu());
	rc.placeModule(eg);
	rc.getCpu().turnOn();
	rc.getCpu().subdue(mp);
	rc.getCpu().subdue(rd);
	rc.getCpu().setRadius(2);

	//sens.setRadius(4);
	mp.placeModule(sens);
	mp.placeModule(eg);
	eg.connect(sens);
	mp.getRobo()[0]->turnOn();

	app.getField().placePlatform(&rc);
	mp.setCoordinates(1, 2);
	app.getField().placePlatform(&mp);
	rd.setCoordinates(5, 3);
	app.getField().placePlatform(&rd);
	/*app.changeCellType({1, 3}, Field::CellType::pointOfInterest);
	app.changeCellType({ 3, 3 }, Field::CellType::pointOfInterest);
	app.changeCellType({ 5, 5 }, Field::CellType::pointOfInterest);
	app.changeCellType({ 4, 5 }, Field::CellType::obstacle);
	app.changeCellType({ 5, 4 }, Field::CellType::obstacle);
	app.changeCellType({ 5, 6 }, Field::CellType::obstacle);
	app.changeCellType({ 6, 5 }, Field::CellType::obstacle);*/

	//std::cout << "rad: " << sens.getRad() << std::endl;
	app.getField().consoleOutField();
	/*std::cout << "iterating through platform map:" << std::endl;
	for (auto it : app.getField().getPlatforms())
	{
		std::cout << "(" << it.first.first <<", " <<it.first.second<<") " << " | " << it.second->getName() << std::endl;
	}*/

	app.play();
	app.getField().consoleOutField();
	/*
	for (int i = 0; i < 5; i++)
	{
		//if (i == 2) continue;
		Robots::KamikazeRobot kr = Robots::KamikazeRobot();
		if (i == 1 || i==3) kr.setCoordinates(i, 3);
		else kr.setCoordinates(i, 1);
		app.getField().placePlatform(&kr);
		app.getAi().getGraph()[kr.getCoordinates()].isTraversable = false;
	}
	*/
	
	/*
	app.getField().consoleOutField();
	std::cout << "Chunks:" << std::endl;
	std::vector<Game::Chunk> chunks = app.getAi().divideField(app.getField());
	for (Game::Chunk& ch : chunks)
	{
		ch.consoleOut(std::cout);
	}*/
	

	/*
	std::cout << std::endl;
	Field::Cell& cell1 = app.getField().getCellByCoordinates(1, 4);
	Field::Cell& cell2 = app.getField().getCellByCoordinates(0, 0);
	std::vector<Robots::Node*> path = app.getAi().path(&cell1, &cell2, app.getField());
	for (Robots::Node* node : path)
	{
		node->consoleOut(std::cout);
	}
	*/
	return 0;
}