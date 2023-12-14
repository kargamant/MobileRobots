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
	Field::Field::OBSTACLE_PERCENTAGE = 70;
	Game::Application app = Game::Application(10, 10);

	std::cout << "total points of interest: " << app.getField().total_poi << std::endl << std::endl;
	std::cout << "Field:" << std::endl;
	app.getField().consoleOutField();
	std::cout << std::endl;
	std::cout << "Robots on field:" << std::endl;
	for (auto it : app.getField().getPlatforms())
	{
		it.second->consoleOut();
	}

	std::cout << std::endl << "Let's start the game!" << std::endl;
	app.play();
	for (auto it : app.getField().getPlatforms())
	{
		for (Robots::Module* mod : it.second->getRobo())
		{
			if (mod != nullptr)
			{
				delete mod;
				mod = nullptr;
			}
		}
		if (it.second->isDynamic)
		{
			delete it.second;
			it.second = nullptr;
		}
	}
	return 0;
}