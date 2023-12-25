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
#include "MenueLib/Menue.h"

int main(int argc, char* argv[])
{
	Field::Field::GROUND_MODE_ON = false;
	Field::Field::OBSTACLE_PERCENTAGE = 70;
	Game::Application app = Game::Application(5, 5);

	//hello
	std::cout << "total points of interest: " << app.getField().total_poi << std::endl << std::endl;
	std::cout << "Field:" << std::endl;
	app.getField().consoleOutField();
	std::cout << std::endl;
	std::cout << "Robots on field:" << std::endl;
	for (auto it : app.getField().getPlatforms())
	{
		it.second->consoleOut();
	}
	/*auto itr = app.getField().getPlatforms().begin();
	while(itr!= app.getField().getPlatforms().end())
	{
		itr.it->value.second->consoleOut();
		~itr;
	}*/
	std::cout << std::endl << "Let's start the game!" << std::endl;


	if (Dialogue::isArg(argv, argv + argc, "-ai"))
	{
		if (Dialogue::isArg(argv, argv + argc, "-wmode")) app.play();
		else if (Dialogue::isArg(argv, argv + argc, "-mthread"))
		{
			app.play_parallel();
		}
		else app.play(false);
		
	}
	else if (Dialogue::isArg(argv, argv + argc, "-sand-box"))
	{
		app.sandBox();
	}
	else
	{
		std::cout << "No mode specified. Bye!" << std::endl;
	}

	
	
	
	app.getField().cleanField();
	return 0;
}