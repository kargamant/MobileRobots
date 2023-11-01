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
		void turnOff(int ind);
		void turnOn(int ind);
	};
}