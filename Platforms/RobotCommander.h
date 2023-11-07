#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"
#include "../Interfaces/Rulling.h"

namespace Robots
{
	class RobotCommander : public Platform, public Moving, public Rulling
	{
	public:
		RobotCommander(int velocity, std::string name, double energy, int slots, int cost, std::pair coordinates, int robots, ManageModule* modules);
		RobotCommander(MobilePlatform& mp, int robots, ManageModule* modules);
		RobotCommander(int velocity, std::string name, double energy, int slots, int cost, std::pair coordinates, ManageOverlay& mo);
		RobotCommander(MobilePlatform& mp, ManageOverlay& mo);

		void moveRobo(int ind, std::pair<int, int> vector) override;
		Cell* getReport(int ind) override;
		void deleteModule(int ind) override;
		void placeModule(int ind) override;
		void move(std::pair<int, int> vector) override;
	};
}