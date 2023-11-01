#include "MobilePlatform.h"
#include "ManageOverlay.h"

namespace Robots
{
	class RobotCommander : public MobilePlatform, public ManageOverlay
	{
	public:
		RobotCommander(int velocity, std::string name, double energy, int slots, int cost, std::pair coordinates, int robots, ManageModule* modules);
		RobotCommander(MobilePlatform& mp, int robots, ManageModule* modules);
		RobotCommander(int velocity, std::string name, double energy, int slots, int cost, std::pair coordinates, ManageOverlay& mo);
		RobotCommander(MobilePlatform& mp, ManageOverlay& mo);
	};
}