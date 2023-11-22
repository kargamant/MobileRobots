#include "ManageModule.h"

namespace Robots
{
	void ManageModule::subdue(Platform& plt)
	{
		Rulling* urmom = dynamic_cast<Rulling*>(getMom());
		if (Field::distance(urmom->getCoordinates(), plt.getCoordinates()) <= radius && urmom->getSubOrd().size() < urmom->getSub()) urmom->getSubOrd().push_back(plt);
		else if (urmom->getSubOrd().size() == urmom->getSub()) throw std::invalid_argument("Error. Platform is full.");
		else throw std::invalid_argument("Error. Cant subdue, platform is unreachable.");
	}

	void ManageModule::release(int ind)
	{
		Rulling* urmom = dynamic_cast<Rulling*>(getMom());
		urmom->checkInd(ind);
		urmom->getSubOrd().erase(urmom->getSubOrd().begin() + ind);
	}
}