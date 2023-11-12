
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
		double energyLevel;
		bool state; //on/off
		Priority priority;
		int cost;
	public:
		Module(double energy, bool state, Priority priority, int cost);
		Module(Module& module);

		double getEnergy() { return energyLevel; }
		bool getState() { return state; }
		Priority getPriority() { return priority; }
		int getCost() { return cost; }

		Module& turnOn();
		Module& turnOff();
	};
}