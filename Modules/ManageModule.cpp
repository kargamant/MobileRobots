#include "../Platforms/CommandCentre.h"
#include "Sensor.h"
#include "../utils/CheckComponent.h"

namespace Robots
{
	void ManageModule::subdue(Platform& plt)
	{
		if(!getState()) throw std::invalid_argument("Error. CPU is off.");
		CommandCentre* urmom = dynamic_cast<CommandCentre*>(getMom());
		ManageModule& urmom_cpu = urmom->getCpu();

		if (Field::inArea(urmom->getCoordinates(), plt.getCoordinates(), radius) && urmom_cpu.getSubOrd().size() < urmom_cpu.getSub())
		{
			checkDuplicate(&plt);
			urmom_cpu.getSubOrd().push_back(&plt);
			plt.setMaster(getMom());
		}
		else if (urmom_cpu.getSubOrd().size() == urmom_cpu.getSub()) throw std::invalid_argument("Error. Platform is full.");
		else throw std::invalid_argument("Error. Cant subdue, platform is unreachable.");
	}

	void ManageModule::release(int ind)
	{
		//CommandCentre* urmom = dynamic_cast<CommandCentre*>(getMom());
		checkInd(ind);
		subordinates[ind]->setMaster(nullptr);
		subordinates.erase(subordinates.begin() + ind);
	}

	void ManageModule::release(Platform* subordinate)
	{
		if (!getState()) throw std::invalid_argument("Error. CPU is off.");
		int ind = 0;
		bool isReleased = false;
		for (Platform* plt : subordinates)
		{
			if (plt == subordinate)
			{
				isReleased = true;
				release(ind);
				subordinates[ind]->setMaster(nullptr);
				break;
			}
			ind++;
		}
		if(!isReleased) throw std::invalid_argument("Error. This is not a subordinate.");
	}

	void ManageModule::checkReachable(int ind)
	{
		if (!Field::inArea(getMom()->getCoordinates(), getSubOrd()[ind]->getCoordinates(), radius)) throw std::invalid_argument("Error. Platform is unreachable.");
	}

	void ManageModule::checkReachable(Platform* plt)
	{
		if (!Field::inArea(getMom()->getCoordinates(), plt->getCoordinates(), radius)) throw std::invalid_argument("Error. Platform is unreachable.");
	}

	void ManageModule::checkInd(int ind)
	{
		if (ind < 0 || ind >= subord) throw std::invalid_argument("Error. Invalid index for manage module.");
		else if (ind >= subordinates.size()) throw std::invalid_argument("Error. Correct index, but no subord with this index.");
	}

	int ManageModule::checkSensor(Platform* plt)
	{
		int k = 0;
		for (Module* mod : plt->getRobo())
		{
			if (!mod->isSensor) k++;
			else return k;
		}
		return -1;
	}

	void ManageModule::checkDuplicate(Platform* plt)
	{
		for (Platform* sub : subordinates)
		{
			if (sub == plt)
			{
				throw std::invalid_argument("Error. You've already subdued this robot.");
			}
		}
	}

	void ManageModule::checkSubOrd(Platform* plt)
	{
		int ind = 0;
		for (Platform* sub : subordinates)
		{
			if (plt == sub)
			{
				break;
			}
			ind++;
		}
		if (ind == subordinates.capacity() || subordinates.size() == 0) throw std::invalid_argument("Error. This is not a subordinate.");

	}

	std::vector<Field::Cell> ManageModule::getReport(Field::Field* fld, int ind)
	{
		checkInd(ind);
		checkReachable(ind);

		Platform* reporter = subordinates[ind];

		int sensor = checkSensor(reporter);
		if (sensor == -1) throw std::invalid_argument("Error. Platform with this coordinates has no sensor module on it. Report is impossible.");
		return dynamic_cast<Sensor*>(reporter->getRobo()[sensor])->scan(fld, motherboard->getCoordinates());
	}

	std::vector<Field::Cell> ManageModule::getReport(Field::Field* fld, Platform* reporter)
	{
		checkReachable(reporter);
		checkSubOrd(reporter);

		int sensor = checkSensor(reporter);
		if (sensor == -1) throw std::invalid_argument("Error. Platform with this coordinates has no sensor module on it. Report is impossible.");
		if (!reporter->getRobo()[sensor]->getState()) throw std::invalid_argument("Error. Reporter's sensor is off.");
		//std::cout << "sensor: " << sensor << std::endl;
		return dynamic_cast<Sensor*>(reporter->getRobo()[sensor])->scan(fld, reporter->getCoordinates());
	}

	void ManageModule::moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector)
	{
		checkInd(ind);
		checkReachable(ind);
		
		fld->movePlatform(subordinates[ind]->getCoordinates(), vector);
	}
}