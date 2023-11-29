#include "Module.h"
#include <vector>

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
		EnergyGenerator(double energySupply = 1, int modules = 3, double energy = 1, bool state = true, Priority priority = Priority::high, int cost = 1000) : energySupply(energySupply), modules(modules), connected(std::vector<Module>(modules)), Module(energySupply, state, priority, cost) { isEnergyGenerator = true; } //automatically set priority to low

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