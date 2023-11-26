#include "../Platforms/CommandCentre.h"
#include "Sensor.h"
#include "../utils/CheckComponent.h"

namespace Robots
{
	void ManageModule::subdue(Platform& plt)
	{
		CommandCentre* urmom = dynamic_cast<CommandCentre*>(getMom());
		ManageModule& urmom_cpu = urmom->getCpu();

		if (Field::distance(urmom->getCoordinates(), plt.getCoordinates()) <= radius && urmom_cpu.getSubOrd().size() < urmom_cpu.getSub()) urmom_cpu.getSubOrd().push_back(plt);
		else if (urmom_cpu.getSubOrd().size() == urmom_cpu.getSub()) throw std::invalid_argument("Error. Platform is full.");
		else throw std::invalid_argument("Error. Cant subdue, platform is unreachable.");
	}

	void ManageModule::release(int ind)
	{
		CommandCentre* urmom = dynamic_cast<CommandCentre*>(getMom());
		checkInd(ind);
		urmom->getCpu().getSubOrd().erase(urmom->getCpu().getSubOrd().begin() + ind);
	}

	void ManageModule::checkReachable(int ind)
	{
		if (Field::distance(getMom()->getCoordinates(), getSubOrd()[ind].getCoordinates()) > radius) throw std::invalid_argument("Error. Platform is unreachable.");
	}

	void ManageModule::checkInd(int ind)
	{
		if (ind < 0 || ind >= subord) throw std::invalid_argument("Error. Invalid index for manage module.");
	}

	int ManageModule::checkSensor(Platform* plt)
	{
		int k = 0;
		for (Module* mod : plt->getRobo())
		{
			if (!isComponentCastable<Module*, Sensor*>(mod)) k++;
			else return k;
		}
		return -1;
	}

	std::vector<Field::Cell> ManageModule::getReport(Field::Field* fld, int ind)
	{
		checkInd(ind);
		checkReachable(ind);

		Platform reporter = subordinates[ind];

		int sensor = checkSensor(&reporter);
		if (sensor == -1) throw std::invalid_argument("Error. Platform with this coordinates has no sensor module on it. Report is impossible.");
		return dynamic_cast<Sensor*>(reporter.getRobo()[sensor])->scan(fld, motherboard->getCoordinates());
	}
	void ManageModule::moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector)
	{
		checkInd(ind);
		checkReachable(ind);
		
		fld->movePlatform(subordinates[ind].getCoordinates(), vector);
	}
}