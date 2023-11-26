#include "Platform.h"
#include <time.h>
#include <iostream>
#include "../Modules/ManageModule.h"
#include "../utils/CheckComponent.h"

namespace Robots
{
	std::string Platform::NICKNAME_FILENAME = "resources/base_nicknames.txt";

	std::string randomRoboName(std::fstream& file)
	{
		const std::string prefixes = "!@#$%^&*()_+";
		std::vector<std::string> base_nicknames;
		int i = 0;
		std::string to_read;
		while (!file.eof())
		{
			file >> to_read;
			base_nicknames.push_back(to_read);
			i++;
		}
		std::srand(time(NULL));
		i = std::rand() % i;
		int k = std::rand() % prefixes.length();

		return (base_nicknames[i]+ prefixes[k] + std::to_string((std::rand() % 10) * 1000));
	}

	Platform::Platform(double energy, int slots, int cost, std::pair<int, int> coordinates): energyLevel(energy), slots(slots), cost(cost), coordinates(coordinates), robo(std::vector<Module*>())
	{
		std::fstream file;
		file.open("../"+NICKNAME_FILENAME, std::ios::in);
		name = randomRoboName(file);
		file.close();
	}
	Platform::Platform(std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates) :energyLevel(energy), slots(slots), cost(cost), coordinates(coordinates), robo(std::vector<Module*>()), name(name) {}

	void Platform::deleteModule(int ind)
	{
		checkInd(ind);
		robo.erase(robo.begin()+ind);
	}

	void Platform::placeModule(int ind, Module& mod)
	{
		checkInd(ind);
		int flag = false;
		try
		{
			dynamic_cast<ManageModule*>(&mod);
		}
		catch (std::bad_cast)
		{
			flag = true;
			if (robo.size() != slots)
			{
				robo.insert(robo.begin() + ind, &mod);
			}
			else
			{
				throw std::invalid_argument("Error. Platform is full.");
			}
		}
		if (!flag) throw std::invalid_argument("Error. Cant place manage module on non rulling platform.");
	}

	void Platform::placeModule(Module& mod)
	{
		if(mod.getIsRulling()) throw std::invalid_argument("Error. Cant place manage module on non rulling platform.");
		else if (robo.size() != slots)
		{
			robo.push_back(&mod);
		}
		else
		{
			throw std::invalid_argument("Error. Platform is full.");
		}
		//if (!flag) throw std::invalid_argument("Error. Cant place manage module on non rulling platform.");
	}

	void Platform::turnOn(int ind)
	{
		checkInd(ind);
		robo[ind]->turnOn();
	}
	void Platform::turnOff(int ind)
	{
		checkInd(ind);
		robo[ind]->turnOff();
	}

	void Platform::checkInd(int ind)
	{
		if (ind > slots || ind < 0) throw std::invalid_argument("Error. Index is incorrect.");
	}
}