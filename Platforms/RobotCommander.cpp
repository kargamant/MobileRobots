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
			std::cout << "coordinates: " << coordinates.first << " " << coordinates.second << std::endl;
			std::cout << "vector: " << vector.first << " " << vector.second << std::endl;
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