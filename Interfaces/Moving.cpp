#include "Moving.h"

namespace Robots
{
	void Moving::move(std::pair<int, int> vector)
	{
		//fld->movePlatform(coordinates, vector);
		coordinates.first += vector.first;
		coordinates.second += vector.second;
	}
}