
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
		Module(double energy = 0, bool state = false, Priority priority = Priority::low, int cost = 0):energyLevel(energy), state(state), priority(priority), cost(cost) {}
		Module(Module& module);

		double getEnergy() { return energyLevel; }
		bool getState() { return state; }
		Priority getPriority() { return priority; }
		int getCost() { return cost; }

		Module& turnOn();
		Module& turnOff();
	};
}