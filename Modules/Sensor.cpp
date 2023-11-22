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

	double Sensor::toRadians()
	{
		switch (angle)
		{
		case ViewAngles::quater:
			return PI / 4;
		case ViewAngles::half:
			return PI / 2;
		case ViewAngles::pie:
			return PI;
		case ViewAngles::tau:
			return 2 * PI;
		}
	}

	std::vector<Field::Cell> Sensor::scan(Field::Field* fld)
	{
		std::vector<Field::Cell> result;
		std::pair<int, int> coordinates = getMom()->getCoordinates();
		std::pair<int, int> tlCorner = { std::max(coordinates.first - radius, 0), std::max(coordinates.second - radius, 0) };
		std::pair<int, int> brCorner = { std::min(coordinates.first + radius, fld->getWidth()), std::min(coordinates.second + radius, fld->getHeight())};
		std::pair<int, int> it = tlCorner;
		double angle_rad = toRadians();
		
		while (it != brCorner)
		{
			if (it == coordinates)
			{
				it.first++;
				continue;
			}
			if (angle==ViewAngles::tau)
			{
				result.push_back(fld->getCellByCoordinates(it));
			}
			else
			{
				std::pair<int, int> point = { it.first - coordinates.first, it.second - coordinates.second };
				int scal = scalar(direction, point);
				double cos = (scal / absVec(direction)) / absVec(point);

				if (cos > std::cos(angle_rad / 2)) result.push_back(fld->getCellByCoordinates(it));
			}
			
			
			

			if (it.first != brCorner.first) it.first++;
			else
			{
				it.first = tlCorner.first;
				it.second++;
			}
		}
		return result;
	}
}