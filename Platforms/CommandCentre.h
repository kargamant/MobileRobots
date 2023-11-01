#include "Platform.h"
#include "ManageOverlay.h"

namespace Robots
{
	//robots are moving anyway, but platforms can stay still
	class CommandCentre: public Platform, public ManageOverlay
	{
	public:
		CommandCentre(int robots, ManageModule* modules, std::string name, double energy, int slots, int cost, std::pair coordinates);
		CommandCentre(int robots, ManageModule* modules, Platform& plt);
		CommandCentre(ManageOverlay& mo, std::string name, double energy, int slots, int cost, std::pair coordinates);
		CommandCentre(ManageOverlay& mo, Platform& plt);
	};
}