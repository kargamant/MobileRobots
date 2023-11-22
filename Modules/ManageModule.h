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
		ManageModule(int radius, int subord, Platform* subordinates, double energy, bool state, Priority priority, int cost); //automatically set priority high on module
		ManageModule(int radius, int subord, Platform* subordinates, Module& mod);

		int getRad() { return radius; }
		ManageModule& setRadius(int nrad) { radius = nrad; return *this; }

		void subdue(Module& subordinate);

		void release(int ind);

		Cell* getReport(int ind) override;
		void moveRobo(int ind, std::pair<int, int> vector) override;
	};
}