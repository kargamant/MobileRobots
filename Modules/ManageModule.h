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
		void subdue(Module& subordinate);

		void release(int ind);
	};
}