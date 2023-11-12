#include "Module.h"
#include "Cell.h"

namespace Robots
{
	class Sensor :public Module
	{
	private:
		int radius;
		std::pair<int, int> direction; //vector from current position to destination point
		int angle;
	public:
		Sensor(int radius, std::pair<int, int> direction, int angle, double energy, bool state, Priority priority, int cost); //automatically sets priority to medium
		Sensor(int radius, std::pair<int, int> direction, int angle, Module& mod);

		int getRad() { return radius; }
		std::pair<int, int> getDirection() { return direction; }
		int getAngle() { return angle; }

		Sensor& setRadius(int nrad) { radius = nrad; return *this; }
		Sensor& setDirection(int x, int y) { direction.first = x; direction.second = y; return *this; }
		Sensor& setAngle(int nangle) { angle = nangle; return *this; }


		Cell* scan();
	};
}