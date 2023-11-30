#include "Module.h"
#include "../Interfaces/Rulling.h"
#include "../Field/Cell.h"
#pragma once

namespace Robots
{

	class ManageModule : public Module, public Rulling
	{
	private:
		Platform* motherboard;
		int radius;
		int subord;
		std::vector<Platform*> subordinates;
		void checkInd(int ind);
		void checkDuplicate(Platform* plt);
		void checkSubOrd(Platform* plt);
	public:
		ManageModule(Platform* mom, int radius=1, int subord=1, double energy=2, bool state=false, Priority priority=Priority::high, int cost=5000) :motherboard(mom), radius(radius), subord(subord), Module(energy, state, priority, cost) { isRulling = true; } //automatically set priority high on module
		//ManageModule(int radius, int subord, Platform* subordinates, Module& mod);

		int getSub() { return subord; }
		std::vector<Platform*>& getSubOrd() { return subordinates; }
		int getRad() { return radius; }
		ManageModule& setRadius(int nrad) { radius = nrad; return *this; }
		Platform* getMom() { return motherboard; }

		void subdue(Platform& plt);
		void release(int ind);
		void release(Platform* subordinate);
		std::vector<Field::Cell> getReport(Field::Field* fld, int ind) override;
		std::vector<Field::Cell> getReport(Field::Field* fld, Platform* reporter);
		void moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector) override;

		void checkReachable(int ind);
		void checkReachable(Platform* plt);
		int checkSensor(Platform* plt);
	};
}