#include "Gun.h"

namespace Robots
{
	void Gun::destroy(Field::Field* fld, std::pair<int, int> coordinates)
	{
		if (Field::distance(getMom()->getCoordinates(), coordinates) > radius) throw std::invalid_argument("Error. Cant this target is too far.");
		fld->destroyCell(coordinates);
	}
}