#include "RobotCommander.h"
#include "MobilePlatform.h"

namespace Robots
{
	void RobotCommander::move(Field::Field* fld, std::pair<int, int> vector)
	{
		try
		{
			fld->movePlatform(coordinates, vector);
		}
		catch (std::invalid_argument)
		{
			throw std::invalid_argument("Error. Commander cant go through this cell.");
		}
		for (Platform* plt : getCpu().getSubOrd())
		{
			try
			{
				dynamic_cast<MobilePlatform&>(*plt).move(fld, vector);
			}
			catch (std::exception)
			{
				continue;
			}
		}
		
	}
}