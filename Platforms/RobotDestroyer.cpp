#include "RobotDestroyer.h"

namespace Robots
{
	RobotDestroyer::RobotDestroyer(int max_radius, int velocity, std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates) :Destroying(max_radius), MobilePlatform(velocity, name, energy, slots, cost, coordinates)
	{
		Gun* robotGun = new Gun(this, energy, true, Priority::low, cost, max_radius);
		placeModule(*robotGun);
		gunInd = 0;
	}

	void RobotDestroyer::destroy(Field::Field* fld, std::pair<int, int> coordinates)
	{
		getGun().destroy(fld, coordinates);
	}
}