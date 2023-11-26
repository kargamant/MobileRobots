#include "MobilePlatform.h"
#include "../Field/Field.h"

namespace Robots
{
	void MobilePlatform::move(Field::Field* fld, std::pair<int, int> vector)
	{
		//std::cout << "db2" << std::endl;
		fld->movePlatform(coordinates, vector);
	}
}