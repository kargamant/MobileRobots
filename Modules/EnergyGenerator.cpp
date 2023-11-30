#include "EnergyGenerator.h"
#include <stdexcept>

namespace Robots
{
	void EnergyGenerator::checkInd(int ind)
	{
		if (ind < 0 || ind >= modules || ind>=connected.size()) throw std::invalid_argument("Error. Index cant be negative or increase size of module vector.");
	}

	void EnergyGenerator::turnOffModule(int ind)
	{
		checkInd(ind);
		currentLoad -= connected[ind]->getEnergy();
		
		connected[ind]->setState(false);
	}
	void EnergyGenerator::turnOnModule(int ind)
	{
		checkInd(ind);
		if ((currentLoad + connected[ind]->getEnergy()) > energySupply) throw std::invalid_argument("Error. Not enough energy to turn on this module.");
		else
		{
			currentLoad += connected[ind]->getEnergy();
			connected[ind]->setState(true);
			
		}
	}

	void EnergyGenerator::connect(Module& mod)
	{
		if (connected.size() < modules)
		{
			if (findModule(&mod) != -1) throw std::invalid_argument("Error. Module has already been connected.");
			mod.turnOff();
			mod.supplier = this;
			connected.push_back(&mod);
		}
		else throw std::invalid_argument("Error. EnergyGenerator is full.");
	}

	void EnergyGenerator::dissconnect(int ind)
	{
		checkInd(ind);
		if (connected[ind]->getState())
		{
			turnOffModule(ind);
		}
		connected[ind]->supplier = nullptr;
		connected.erase(connected.begin() + ind);
	}

	Module& EnergyGenerator::turnOn()
	{
		setState(true);
		for (Module* mod : connected)
		{
			turnOnModule(mod);
		}
		return *this;
	}

	//basically kills module
	Module& EnergyGenerator::turnOff()
	{
		setState(false);
		for (Module* mod : connected)
		{
			turnOffModule(mod);
		}
		return *this;
	}

	int EnergyGenerator::findModule(Module* mod)
	{
		int ind = 0;
		for (Module* m : connected)
		{
			if (m == mod)
			{
				return ind;
			}
			++ind;
		}
		return -1;
		//throw std::invalid_argument("Error. This module is not connected.");
	}

	void EnergyGenerator::turnOffModule(Module* mod)
	{
		int ind = findModule(mod);
		if(ind==-1) throw std::invalid_argument("Error. This module is not connected.");
		turnOffModule(ind);
	}
	void EnergyGenerator::turnOnModule(Module* mod)
	{
		int ind = findModule(mod);
		if (ind == -1) throw std::invalid_argument("Error. This module is not connected.");
		turnOnModule(ind);
	}
	void EnergyGenerator::dissconnect(Module* mod)
	{
		int ind = findModule(mod);
		if (ind == -1) throw std::invalid_argument("Error. This module is not connected.");
		dissconnect(ind);
		//mod->supplier = nullptr;
	}
}