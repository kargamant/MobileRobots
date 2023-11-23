#include "Rulling.h"
#include "../Modules/Module.h"
#include "../Modules/Sensor.h"
#include "../Modules/ManageModule.h"
#include "../CheckComponent.h"

namespace Robots
{
	void Rulling::checkReachable(Field::Field* fld, int ind)
	{
		if (fld->distance(subordinates[ind].getCoordinates(), coordinates) > radius) throw std::invalid_argument("Error. Robot is not reachable from rulling robot.");
	}

	std::vector<Field::Cell> Rulling::getReport(Field::Field* fld, int ind)
	{
		checkInd(ind);
		checkReachable(fld, ind);

		Platform reporter = subordinates[ind];

		int sensor=checkSensor(&reporter);
		if(sensor==-1) throw std::invalid_argument("Error. Platform with this coordinates has no sensor module on it. Report is impossible.");
		return dynamic_cast<Sensor&>(reporter.getRobo()[sensor]).scan(fld, coordinates);
	}

	void Rulling::moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector)
	{
		checkInd(ind);
		checkReachable(fld, ind);

		fld->movePlatform(subordinates[ind].getCoordinates(), vector);
	}
	
	void Rulling::checkInd(int ind)
	{
		if (ind >= subord) throw std::invalid_argument("Error. Index is greater than number of subordinates.");
	}

	void Rulling::placeModule(int ind, Module& mod)
	{
		checkInd(ind);
		if (robo.size() != slots)
		{
			robo.insert(robo.begin() + ind, mod);
		}
		else
		{
			throw std::invalid_argument("Error. Platform is full.");
		}
	}

	void Rulling::deleteModule(int ind)
	{
		checkInd(ind);
		int flag = false;
		try
		{
			dynamic_cast<ManageModule&>(robo[ind]);
		}
		catch (std::bad_cast)
		{
			flag = true;
			robo.erase(robo.begin() + ind);
		}
		if (!flag) throw std::invalid_argument("Error. Cant delete manage module from rulling platform.");
	}

	/*Module* Rulling::getManageModule()
	{
		for (Module& mod : getRobo())
		{

		}
	}*/

	/*void Rulling::subdue(Platform& plt)
	{
		if (Field::distance(coordinates, plt.getCoordinates()) <= radius && subordinates.size() < slots) subordinates.push_back(plt);
		else if (subordinates.size() < slots) throw std::invalid_argument("Error. Platform is full.");
		else throw std::invalid_argument("Error. Cant subdue, platform is unreachable.");
	}

	void Rulling::release(int ind)
	{
		checkInd(ind);
		subordinates.erase(subordinates.begin() + ind);
	}*/

	int checkSensor(Platform* plt)
	{
		int k = 0;
		for (Module& mod : plt->getRobo())
		{
			if (!isComponentCastable<Module&, Sensor&>(mod)) k++;
			else return k;
		}
		return -1;
	}
}