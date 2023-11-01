#include "../Modules/ManageModule.h"
#include "../Field/Cell.h"

namespace Robots
{
	class ManageOverlay
	{
	private:
		Table* info;
		int robots;
		ManageModule* modules;
	public:
		Cell* getReport(int ind);
		void move(int ind, std::pair vector);
	};
}