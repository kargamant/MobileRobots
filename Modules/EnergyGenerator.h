#include "Module.h"

namespace Robots
{
	class EnergyGenerator :public Module
	{
	private:
		double energySupply;
		int modules;
		Module* connected;
	public:
		EnergyGenerator(double energySupply, int modules, Module* connected, double energy, bool state, Priority priority, int cost); //automatically set priority to low
		EnergyGenerator(double energySupply, int modules, Module* connected, Module& mod);

		double getEnergySup() { return energySupply; }
		int getModules() { return modules; }
		Module* getConnected() { return connected; }

		EnergyGenerator& setEnergySup(double nsup) { energySupply = nsup; return *this; }

		void turnOff(int ind);
		void turnOn(int ind);
	};
}