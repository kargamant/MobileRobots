#include "QuantumPlatform.h"

namespace Robots
{
	void QuantumPlatform::link(QuantumPlatform& platform)
	{
		platforms.push_back(platform);
		linked++;
	}

	void QuantumPlatform::teleport(Field::Field* fld, int ind)
	{
		std::pair<int, int> dest = platforms[ind].getCoordinates();
		std::pair<int, int> vector = { dest.first - coordinates.first, dest.second - coordinates.second };
		fld->movePlatform(coordinates, vector);
		fld->movePlatform(coordinates, {-vector.first, -vector.second});
	}

	void QuantumPlatform::deleteModule(int ind)
	{
		robo.erase(robo.begin() + ind);
		//remake using refference
		for (QuantumPlatform& qp : platforms)
		{
			qp.robo.erase(robo.begin() + ind);
		}
	}

	void QuantumPlatform::placeModule(Module& mod)
	{
		robo.push_back(mod);
		//remake using refference
		for (QuantumPlatform& qp : platforms)
		{
			qp.robo.push_back(mod);
		}
	}
}