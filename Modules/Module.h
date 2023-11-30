#pragma once
#include <string>
//#include "EnergyGenerator.h"

namespace Robots
{
	enum class Priority
	{
		low,
		medium,
		high
	};

	std::string priorityToString(Priority pr);

	class Module
	{
	private:
		double energyLevel;
		bool state; //on/off
		Priority priority;
		int cost;
	public:
		Module* supplier = nullptr;
		bool isRulling = false;
		bool isGun = false;
		bool isSensor = false;
		bool isEnergyGenerator = false;
		Module(double energy = 0, bool state = false, Priority priority = Priority::low, int cost = 0):energyLevel(energy), state(state), priority(priority), cost(cost) {}

		double getEnergy() { return energyLevel; }
		bool getState() { return state; }
		Priority getPriority() { return priority; }
		int getCost() { return cost; }
		bool getIsRulling() { return isRulling; }
		Module& setState(bool nstate) { state = nstate; return *this; }

		virtual Module& turnOn(); //{ state = true; return *this; }
		virtual Module& turnOff();// { state = false; return *this; }
	};
}