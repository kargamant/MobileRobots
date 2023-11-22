#include "Module.h"
#include "../Interfaces/Rulling.h"
#include "../Field/Cell.h"

namespace Robots
{

	class ManageModule : public Module
	{
	private:
		int radius;
	public:
		ManageModule(int radius, Platform* mom, double energy, bool state, Priority priority, int cost) :radius(radius), Module(mom, energy, state, priority, cost) {} //automatically set priority high on module
		//ManageModule(int radius, int subord, Platform* subordinates, Module& mod);

		int getRad() { return radius; }
		ManageModule& setRadius(int nrad) { radius = nrad; return *this; }

		void subdue(Platform& plt);
		void release(int ind);
	};
}