#include "EnergyGenerator.h"

namespace Robots
{
	void EnergyGenerator::checkInd(int ind)
	{
		if (ind < 0 || ind >= modules) throw std::invalid_argument("Error. Index cant be negative or increase size of module vector.");
	}

	void EnergyGenerator::turnOffModule(int ind)
	{
		checkInd(ind);
		connected[ind].turnOff();
	}
	void EnergyGenerator::turnOnModule(int ind)
	{
		checkInd(ind);
		connected[ind].turnOn();
	}

	void EnergyGenerator::connect(Module& mod)
	{
		if (connected.size() < modules)
		{
			connected.push_back(mod);
		}
		else throw std::invalid_argument("Error. EnergyGenerator is full.");
	}

	void EnergyGenerator::dissconnect(int ind)
	{
		checkInd(ind);
		connected.erase(connected.begin() + ind);
	}

	Module& EnergyGenerator::turnOn()
	{
		setState(true);
		for (Module& mod : connected)
		{
			mod.turnOn();
		}
		return *this;
	}

	//basically kills robot
	Module& EnergyGenerator::turnOff()
	{
		setState(false);
		for (Module& mod : connected)
		{
			mod.turnOff();
		}
		return *this;
	}
}