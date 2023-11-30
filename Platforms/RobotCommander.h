#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"
#include "../Interfaces/Rulling.h"
#include "CommandCentre.h"

namespace Robots
{
	class RobotCommander : public Moving, public CommandCentre
	{
	public:
		RobotCommander(int velocity = 0, int radius = 1, int sub = 2, double energy = 3, int slots = 2, int cost = 5000, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) : Moving(velocity), CommandCentre(radius, sub, energy, slots, cost, coordinates) {}

		void move(Field::Field* fld, std::pair<int, int> vector) override;
	};
}