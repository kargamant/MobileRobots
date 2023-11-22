#include "CommandCentre.h"
#include "../Interfaces/Rulling.h"

namespace Robots
{
	void CommandCentre::moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector)
	{
		checkInd(ind);
		
		fld->movePlatform(getSubOrd()[ind].getCoordinates(), vector);
	}


}