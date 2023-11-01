
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
		Module& turnOn();
		Module& turnOff();

		double getEnergyLevel() { return energyLevel; }
	};
}