#include "Gun.h"

namespace Robots
{
	void Gun::destroy(Field::Field* fld, std::pair<int, int> coordinates)
	{
		if (!Field::inArea(getMom()->getCoordinates(), coordinates, max_radius)) throw std::invalid_argument("Error. This target is too far.");
		fld->destroyCell(coordinates);
	}
}