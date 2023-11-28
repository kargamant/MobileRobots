#include "../Interfaces/Platform.h"
#include "Module.h"
#include "../Field/Cell.h"
#include "../Field/Field.h"

namespace Robots
{
	enum class ViewAngles
	{
		quater,
		half,
		pie,
		tau
	};

	int scalar(std::pair<int, int> cell1, std::pair<int, int> cell2);
	double absVec(std::pair<int, int> vec);
	double toRadians(ViewAngles angle);

	class Sensor :public Module
	{
	private:
		int radius;
		std::pair<int, int> direction; //vector from current position to destination point
		ViewAngles angle;
	public:
		static double PI;
		Sensor(int radius = 1, std::pair<int, int> direction = {1, 1}, ViewAngles angle=ViewAngles::tau, double energy=2, bool state=true, Priority priority=Priority::high, int cost=2000) :radius(radius), direction(direction), angle(angle), Module(energy, state, priority, cost) {} //automatically sets priority to medium

		int getRad() { return radius; }
		std::pair<int, int> getDirection() { return direction; }
		ViewAngles getAngle() { return angle; }

		Sensor& setRadius(int nrad) { radius = nrad; return *this; }
		Sensor& setDirection(int x, int y) { direction.first = x; direction.second = y; return *this; }
		Sensor& setAngle(ViewAngles nangle) { angle = nangle; return *this; }

		std::vector<Field::Cell> scan(Field::Field* fld, std::pair<int, int> mom_coordinates);
	};
}