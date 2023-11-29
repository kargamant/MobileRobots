#include "../Interfaces/Platform.h"
#include "../Interfaces/Rulling.h"
#include "../Modules/ManageModule.h"
#pragma once

namespace Robots
{
	//robots are moving anyway, but platforms can stay still
	class CommandCentre: public Rulling, public Platform
	{
	private:
		int manageInd;
		CommandCentre& setManageInd(int nmind) { manageInd = nmind; return *this; }
	public:
		CommandCentre(int radius = 0, int sub = 2, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0));

		int getManageInd() const { return manageInd; }
		ManageModule& getCpu() { return *(dynamic_cast<ManageModule*>(getRobo()[manageInd])); }

		std::vector<Field::Cell> getReport(Field::Field* fld, int ind) override;
		std::vector<Field::Cell> getReport(Field::Field* fld, Platform* reporter);
		void moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector) override;
		void deleteModule(int ind) override;
		void placeModule(int ind, Module& mod) override;
		void placeModule(Module& mod) override;
	};
}