#include "Platform.h"
#include <time.h>
#include <iostream>
#include "../Modules/ManageModule.h"
#include "../utils/CheckComponent.h"
#include "../Modules/EnergyGenerator.h"
#include "../Modules/ManageModule.h"
#include "../Game/ViewModule.h"

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

	void Platform::deleteModule(Module* mod)
	{
		bool isDeleted = false;
		int ind = 0;
		for (Module* md : robo)
		{
			if (md == mod)
			{
				if (md->isEnergyGenerator)
				{
					for (Module* m : dynamic_cast<EnergyGenerator&>(*md).getConnected())
					{
						dynamic_cast<EnergyGenerator&>(*md).dissconnect(m);
					}
				}
				else if (md->isRulling)
				{
					for (Platform* sub : dynamic_cast<ManageModule&>(*md).getSubOrd())
					{
						dynamic_cast<ManageModule&>(*md).release(sub);
					}
				}
				isDeleted = true;
				robo.erase(robo.begin()+ind);
				break;
			}
			ind++;
		}
		if (!isDeleted) throw std::invalid_argument("Error. No such module on platform.");
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

	void Platform::turnOn(Module* mod)
	{
		int ind = 0;
		bool isOn = false;
		for (Module* m : robo)
		{
			if (m == mod)
			{
				turnOn(ind);
				isOn = true;
				break;
			}
			++ind;
		}
		if (!isOn) throw std::invalid_argument("Error. No such module on platform.");
	}
	void Platform::turnOff(Module* mod)
	{
		int ind = 0;
		bool isOff = false;
		for (Module* m : robo)
		{
			if (m == mod)
			{
				turnOff(ind);
				isOff = true;
				break;
			}
			++ind;
		}
		if (!isOff) throw std::invalid_argument("Error. No such module on platform.");
	}

	void Platform::checkInd(int ind)
	{
		if (ind > slots || ind < 0) throw std::invalid_argument("Error. Index is incorrect.");
	}

	std::string priorityToString(Priority pr)
	{
		switch (pr)
		{
		case Priority::high:
			return "high";
		case Priority::medium:
			return "medium";
		case Priority::low:
			return "low";
		}
		return "";
	}

	void Platform::consoleOut(std::ostream& stream)
	{
		std::string out = std::format("{} | ({}, {}) | Modules: ", name, std::to_string(coordinates.first), std::to_string(coordinates.second));
		for (Module* mod : robo)
		{
			out += moduleToString(*mod) + ", ";
		}
		stream << out << std::endl;
	}
}