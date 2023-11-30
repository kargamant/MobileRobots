#include "Module.h"
#include <vector>

namespace Robots
{
	class EnergyGenerator :public Module
	{
	private:
		double energySupply;
		double currentLoad;
		int modules;
		std::vector<Module*> connected;
		void checkInd(int ind);
	public:
		EnergyGenerator(double energySupply = 5, int modules = 5, double energy = 1, bool state = true, Priority priority = Priority::high, int cost = 3000) : energySupply(energySupply), modules(modules), connected(std::vector<Module*>()), Module(energySupply, state, priority, cost) { isEnergyGenerator = true; currentLoad = 0; } //automatically set priority to low

		double getEnergySup() { return energySupply; }
		double getCurrentLoad() { return currentLoad; }
		int getModules() { return modules; }
		std::vector<Module*> getConnected() { return connected; }

		EnergyGenerator& setEnergySup(double nsup) { energySupply = nsup; return *this; }

		//turn off/on modules supplied by EnergyGenerator
		void turnOffModule(int ind);
		void turnOnModule(int ind);
		void dissconnect(int ind);
		void turnOffModule(Module* mod);
		void turnOnModule(Module* mod);
		void dissconnect(Module* mod);
		void connect(Module& mod);

		int findModule(Module* mod);
		//override of Module's virtual turn on/off that turn on/off generator itself and all connected modules recursively
		Module& turnOn() override;
		Module& turnOff() override;
	};
}