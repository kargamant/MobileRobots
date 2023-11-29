#include "CommandCentre.h"
#include "../Interfaces/Rulling.h"
#include "../Modules/Sensor.h"

namespace Robots
{
	CommandCentre::CommandCentre(int radius, int sub, double energy, int slots, int cost, std::pair<int, int> coordinates) :Rulling(radius), Platform(energy, slots, cost, coordinates)
	{
		ManageModule* centreCpu = new ManageModule(this, radius, sub, energy, true, Priority::high, cost);
		//std::cout << "db1" << std::endl;
		placeModule(*centreCpu);
		//std::cout << "db2" << std::endl;
		manageInd = 0;
	}

	std::vector<Field::Cell> CommandCentre::getReport(Field::Field* fld, int ind)
	{
		checkInd(ind);
		getCpu().checkReachable(ind);

		Platform* reporter = getCpu().getSubOrd()[ind];

		int sensor = getCpu().checkSensor(reporter);
		if (sensor == -1) throw std::invalid_argument("Error. Platform with this coordinates has no sensor module on it. Report is impossible.");
		return dynamic_cast<Sensor*>(reporter->getRobo()[sensor])->scan(fld, coordinates);
	}

	std::vector<Field::Cell> CommandCentre::getReport(Field::Field* fld, Platform* reporter)
	{
		return getCpu().getReport(fld, reporter);
	}

	void CommandCentre::moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector)
	{
		checkInd(ind);
		
		fld->movePlatform(getCpu().getSubOrd()[ind]->getCoordinates(), vector);
	}

	void CommandCentre::deleteModule(int ind)
	{
		checkInd(ind);
		int flag = false;
		try
		{
			dynamic_cast<ManageModule*>(robo[ind]);
		}
		catch (std::bad_cast)
		{
			flag = true;
			robo.erase(robo.begin() + ind);
		}
		if (!flag) throw std::invalid_argument("Error. Cant delete manage module from rulling platform.");
	}

	void CommandCentre::placeModule(int ind, Module& mod)
	{
		checkInd(ind);
		if (robo.size() != slots)
		{
			robo.insert(robo.begin() + ind, &mod);
		}
		else
		{
			throw std::invalid_argument("Error. Platform is full.");
		}
	}

	void CommandCentre::placeModule(Module& mod)
	{
		std::cout << robo.size() << std::endl;
		if (robo.size() != slots)
		{
			robo.push_back(&mod);
		}
		else
		{
			throw std::invalid_argument("Error. Platform is full.");
		}
	}
}