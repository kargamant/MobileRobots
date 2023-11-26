#pragma once
#include <string>

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
	protected:
		bool isRulling = false;
		Module& setState(bool nstate) { state = nstate; return *this; }
	public:
		Module(double energy = 0, bool state = false, Priority priority = Priority::low, int cost = 0):energyLevel(energy), state(state), priority(priority), cost(cost) {}

		double getEnergy() { return energyLevel; }
		bool getState() { return state; }
		Priority getPriority() { return priority; }
		int getCost() { return cost; }
		bool getIsRulling() { return isRulling; }

		virtual Module& turnOn() { state = true; return *this; }
		virtual Module& turnOff() { state = false; return *this; }
	};
}