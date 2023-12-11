#include "Sensor.h"
#include <math.h>

namespace Robots
{
	double Sensor::PI = 2 * std::acos(0.0);

	int scalar(std::pair<int, int> cell1, std::pair<int, int> cell2)
	{
		return cell1.first * cell2.first + cell1.second * cell2.second;
	}

	double absVec(std::pair<int, int> vec)
	{
		return std::sqrt(vec.first * vec.first + vec.second * vec.second);
	}

	double toRadians(ViewAngles angle)
	{
		switch (angle)
		{
		case ViewAngles::quater:
			return Sensor::PI / 4;
		case ViewAngles::half:
			return Sensor::PI / 2;
		case ViewAngles::pie:
			return Sensor::PI;
		case ViewAngles::tau:
			return 2 * Sensor::PI;
		}
		return 0;
	}

	std::string angleToString(ViewAngles angle)
	{
		switch (angle)
		{
		case ViewAngles::quater:
			return "pi/4";
		case ViewAngles::half:
			return "pi/2";
		case ViewAngles::pie:
			return "pi";
		case ViewAngles::tau:
			return "2pi";
		}
		return 0;
	}

	std::vector<Field::Cell> Sensor::scan(Field::Field* fld, std::pair<int, int> mom_coordinates)
	{
		std::vector<Field::Cell> result;
		std::pair<int, int> coordinates = mom_coordinates;
		std::pair<int, int> tlCorner = { std::max(coordinates.first - radius, 0), std::max(coordinates.second - radius, 0) };
		std::pair<int, int> brCorner = { std::min(coordinates.first + radius, fld->getWidth()-1), std::min(coordinates.second + radius, fld->getHeight()-1)};
		std::pair<int, int> it = tlCorner;
		double angle_rad = toRadians(angle);
		bool isBrChecked = false;
		while (!isBrChecked)
		{
			if (it == coordinates)
			{
				if (it == brCorner)
				{
					isBrChecked = true;
					continue;
				}
				if (it.second == brCorner.second)
				{
					it.second = tlCorner.second;
					it.first++;
				}
				else it.second++;
				continue;
			}
			if (angle==ViewAngles::tau)
			{
				result.push_back(fld->getCellByCoordinates(it));
				//std::cout << "pushable: " << it.first << " " << it.second << std::endl;
			}
			else
			{
				std::pair<int, int> point = { it.first - coordinates.first, it.second - coordinates.second };
				int scal = scalar(direction, point);
				double cos = (scal / absVec(direction)) / absVec(point);

				if (cos > std::cos(angle_rad / 2)) result.push_back(fld->getCellByCoordinates(it));
			}
			
			
			
			if (it == brCorner)
			{
				isBrChecked = true;
				continue;
			}
			if (it.second != brCorner.second) it.second++;
			else
			{
				it.second = tlCorner.second;
				it.first++;
			}
		}
		return result;
	}
}