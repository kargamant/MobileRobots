#pragma once

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
		//Platform* motherboard;
		double energyLevel;
		bool state; //on/off
		Priority priority;
		int cost;
	protected:
		Module& setState(bool nstate) { state = nstate; return *this; }
	public:
		//Platform* mom=nullptr,
		//motherboard(mom), 
		Module(double energy = 0, bool state = false, Priority priority = Priority::low, int cost = 0):energyLevel(energy), state(state), priority(priority), cost(cost) {}

		double getEnergy() { return energyLevel; }
		bool getState() { return state; }
		Priority getPriority() { return priority; }
		int getCost() { return cost; }
		//Platform* getMom() { return motherboard; }

		virtual Module& turnOn() { state = true; return *this; }
		virtual Module& turnOff() { state = false; return *this; }
		//virtual methods to be added
		//virtual std::vector<Field::Cell> scan(Field::Field* fld)=0;
	};
	//urmom = you.getMom()
}