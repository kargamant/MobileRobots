#include "Module.h"
#include "Cell.h"

namespace Robots
{
	class Sensor :public Module
	{
	private:
		int radius;
		std::pair direction; //vector from current position to destination point
		int angle;
	public:
		Sensor(int radius, std::pair direction, int angle, double energy, bool state, Priority priority, int cost); //automatically sets priority to medium
		Sensor(int radius, std::pair direction, int angle, Module& mod);

		Cell* scan();
	};
}