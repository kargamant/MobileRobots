#include "Module.h"
#include "../Interfaces/Rulling.h"

namespace Robots
{
	class ManageModule : public Module, public Rulling
	{
	private:
		int radius;
		int subord;
		Platform* subordinates;
	public:
		ManageModule(int radius, int subord, Module* subordinates, double energy, bool state, Priority priority, int cost); //automatically set priority high on module
		ManageModule(int radius, int subord, Module* subordinates, Module& mod);

		void subdue(Module& subordinate);

		void release(int ind);

		Cell* getReport(int ind) override;
		void moveRobo(int ind, std::pair<int, int> vector) override;
	};
}