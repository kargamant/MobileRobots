#include "Module.h"

namespace Robots
{
	class EnergyGenerator :public Module
	{
	private:
		double energySupply;
		int modules;
		std::vector<Module> connected;
		void checkInd(int ind);
	public:
		EnergyGenerator(double energySupply, int modules, std::vector<Module> connected, double energy, bool state, Priority priority, int cost) : energySupply(energySupply), modules(modules), connected(std::vector<Module>(modules)), Module(energySupply, state, priority, cost) {} //automatically set priority to low
		//EnergyGenerator(double energySupply, int modules, std::vector<Module> connected, Module& mod);

		double getEnergySup() { return energySupply; }
		int getModules() { return modules; }
		std::vector<Module> getConnected() { return connected; }

		EnergyGenerator& setEnergySup(double nsup) { energySupply = nsup; return *this; }

		//turn off/on modules supplied by EnergyGenerator
		void turnOffModule(int ind);
		void turnOnModule(int ind);
		void connect(Module& mod);
		void dissconnect(int ind);

		//override of Module's virtual turn on/off that turn on/off generator itself and all connected modules recursively
		Module& turnOn() override;
		Module& turnOff() override;
	};
}