#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"
#include "../Interfaces/Rulling.h"
#include "CommandCentre.h"

namespace Robots
{
	class RobotCommander : public Moving, public CommandCentre
	{
	public:
		RobotCommander(int velocity = 0, int radius = 1, int sub = 3, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) : Moving(velocity), CommandCentre(radius, sub, energy, slots, cost, coordinates) {}

		void move(Field::Field* fld, std::pair<int, int> vector) override;
	};
}