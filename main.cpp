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
#include <time.h>
#include <fstream>

int main(int argc, char* argv[])
{
	Field::Field::GROUND_MODE_ON = false;
	Field::Field::OBSTACLE_PERCENTAGE = 70;
	Game::Application app = Game::Application(20, 20);

	//hello
	std::cout << "total points of interest: " << app.getField().total_poi << std::endl << std::endl;
	std::cout << "Field:" << std::endl;
	app.getField().consoleOutField();
	//exit(0);
	std::cout << std::endl;
	std::cout << "Robots on field:" << std::endl;

	std::vector<Robots::Platform*> potential_subs;
	Robots::Platform* ruller;
	for (auto it : app.getField().getPlatforms())
	{
		it.second->consoleOut();
		
		if (!it.second->getIsMaster())
		{
			potential_subs.push_back(it.second);
		}
		else
		{
			ruller = it.second;
		}
	}
	dynamic_cast<Robots::CommandCentre*>(ruller)->getCpu().setRadius(app.getField().getWidth()/2);
	for (auto it : potential_subs)
	{
		try
		{
			dynamic_cast<Robots::CommandCentre*>(ruller)->getCpu().subdue(*it);

		}
		catch (std::invalid_argument)
		{
			continue;
		}
	}
	std::cout << "fectively subdued: " << dynamic_cast<Robots::CommandCentre*>(ruller)->getCpu().getSubOrd().size() << std::endl;
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
			double start = (double)time(NULL) / (double)CLOCKS_PER_SEC;
			app.play_parallel();
			double finish = (double)time(NULL) / (double)CLOCKS_PER_SEC;
			//std::cout << std::endl << "Time passed: " << finish - start << std::endl;
			printf("Time passed: %.10lf\n", (finish - start));
		}
		else
		{
			double start = (double)time(NULL) / (double)CLOCKS_PER_SEC;
			app.play(false);
			double finish = (double)time(NULL) / (double)CLOCKS_PER_SEC;
			//std::cout << std::endl << "Time passed: " << finish - start << std::endl;
			printf("Time passed: %.10lf\n", (finish - start));

		}
		
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