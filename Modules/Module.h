#pragma once
#include "../Interfaces/Platform.h"

namespace Robots
{
	enum class Priority
	{
		low,
		medium,
		high
	};

	class Module
	{
	private:
		Platform* motherboard;
		double energyLevel;
		bool state; //on/off
		Priority priority;
		int cost;
	public:
		Module(Platform* mom, double energy = 0, bool state = false, Priority priority = Priority::low, int cost = 0):motherboard(mom), energyLevel(energy), state(state), priority(priority), cost(cost) {}

		double getEnergy() { return energyLevel; }
		bool getState() { return state; }
		Priority getPriority() { return priority; }
		int getCost() { return cost; }

		virtual Module& turnOn() { state = true; return *this; }
		virtual Module& turnOff() { state = false; return *this; }
		//virtual methods to be added
		//virtual std::vector<Field::Cell> scan(Field::Field* fld)=0;
	};
}