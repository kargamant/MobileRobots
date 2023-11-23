#include "Module.h"
#include "../Interfaces/Rulling.h"
#include "../Field/Cell.h"

namespace Robots
{

	class ManageModule : public Module
	{
	private:
		Platform* motherboard;
		int radius;
	public:
		ManageModule(Platform* mom, int radius, double energy, bool state, Priority priority, int cost) :motherboard(mom), radius(radius), Module(energy, state, priority, cost) {} //automatically set priority high on module
		//ManageModule(int radius, int subord, Platform* subordinates, Module& mod);

		int getRad() { return radius; }
		ManageModule& setRadius(int nrad) { radius = nrad; return *this; }
		Platform* getMom() { return motherboard; }

		void subdue(Platform& plt);
		void release(int ind);
	};
}