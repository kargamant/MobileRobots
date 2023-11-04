#include "../Modules/ManageModule.h"
#include "../Field/Cell.h"

namespace Robots
{
	class ManageOverlay
	{
	private:
		int robots;
		ManageModule* modules;
	public:
		ManageOverlay(int robots, ManageModule* modules);
		ManageOverlay(ManageOverlay& mo);

		Cell* getReport(int ind);
		void move(int ind, std::pair vector); //moves a robot
	};
}