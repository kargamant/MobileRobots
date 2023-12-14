#include "Game/Application.h"
#include <iostream>
#include "Platforms/KamikazeRobot.h"
#include "Platforms/RobotCommander.h"
#include "Modules/Gun.h"
#include "Platforms/MobilePlatform.h"
#include "Modules/EnergyGenerator.h"
#include "Modules/Sensor.h"
#include "Platforms/RobotDestroyer.h"
#include "utils/CheckComponent.h"

int main()
{
	Field::Field::GROUND_MODE_ON = false;
	Field::Field::OBSTACLE_PERCENTAGE = 50;
	Game::Application app = Game::Application(7, 7);

	app.getField().consoleOutField();
	for (auto it : app.getField().getPlatforms())
	{
		it.second->consoleOut();
	}
	/*Robots::RobotCommander rc = Robots::RobotCommander();
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
	//rc.getCpu().subdue(mp);
	//rc.getCpu().subdue(rd);
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
	app.getField().placePlatform(&rd);*/
	
	//app.updateGraphTraversity();
	app.getField().consoleOutField();
	app.play();
	app.getField().consoleOutField();
	
	return 0;
}