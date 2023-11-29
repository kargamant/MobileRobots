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

	void RobotDestroyer::deleteModule(Module* mod)
	{
		bool isDeleted = false;
		int ind = 0;
		for (Module* md : robo)
		{
			if (md == mod)
			{
				if (ind == gunInd) throw std::invalid_argument("Error. Cant delete gun from robot-destroyer.");
				isDeleted = true;
				robo.erase(robo.begin() + ind);
				break;
			}
			ind++;
		}
		if (!isDeleted) throw std::invalid_argument("Error. No such module on platform.");
	}

	void RobotDestroyer::deleteModule(int ind)
	{
		checkInd(ind);
		int flag = false;
		try
		{
			dynamic_cast<Gun*>(robo[ind]);
		}
		catch (std::bad_cast)
		{
			flag = true;
			robo.erase(robo.begin() + ind);
		}
		if (!flag) throw std::invalid_argument("Error. Cant delete gun from robot destroyer.");
	}
}