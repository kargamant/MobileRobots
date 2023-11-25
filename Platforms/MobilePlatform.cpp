#include "MobilePlatform.h"
#include "../Field/Field.h"

namespace Robots
{
	void MobilePlatform::move(Field::Field* fld, std::pair<int, int> vector)
	{
		fld->movePlatform(coordinates, vector);
	}
}