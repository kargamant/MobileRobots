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
		CommandCentre(int radius = 1, int sub = 2, double energy = 3, int slots = 3, int cost = 5000, std::pair<int, int> coordinates = std::pair<int, int>(0, 0));
		~CommandCentre()
		{
			delete &getCpu();
		}

		int getManageInd() const { return manageInd; }
		ManageModule& getCpu() { return *(dynamic_cast<ManageModule*>(getRobo()[manageInd])); }

		std::vector<Field::Cell> getReport(Field::Field* fld, int ind) override;
		std::vector<Field::Cell> getReport(Field::Field* fld, Platform* reporter);
		void moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector) override;
		void deleteModule(int ind) override;
		void deleteModule(Module* mod) override;
		void placeModule(int ind, Module& mod) override;
		void placeModule(Module& mod) override;

		//void turnOn(Module* mod) override;
		//void turnOff(int ind) override;
		//void turnOff(Module* mod) override;
	};
}