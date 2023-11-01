#include "Module.h"

namespace Robots
{
	class ManageModule : public Module
	{
	private:
		int radius;
		int subord;
		Module* subordinates;
	public:
		ManageModule(int radius, int subord, Module* subordinates, double energy, bool state, Priority priority, int cost); //automatically set priority high on module
		ManageModule(int radius, int subord, Module* subordinates, Module& mod);

		void subdue(Module& subordinate);

		void release(int ind);
	};
}