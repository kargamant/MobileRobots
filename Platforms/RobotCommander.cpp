#include "RobotCommander.h"
#include "MobilePlatform.h"

namespace Robots
{
	void RobotCommander::move(Field::Field* fld, std::pair<int, int> vector)
	{
		for (Platform& plt : getCpu().getSubOrd())
		{
			try
			{
				dynamic_cast<MobilePlatform&>(plt).move(fld, vector);
			}
			catch (std::bad_cast)
			{
				continue;
			}
		}
		fld->movePlatform(coordinates, vector);
	}
}