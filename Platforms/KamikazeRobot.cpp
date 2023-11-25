#include "KamikazeRobot.h"

namespace Robots
{
	void KamikazeRobot::destroy(Field::Field* fld, std::pair<int, int> coordinates)
	{
		fld->destroyArea(getMaxRadius(), getCoordinates());
	}
}