#include "../Interfaces/Platform.h"
#include "../Interfaces/Rulling.h"

namespace Robots
{
	//robots are moving anyway, but platforms can stay still
	class CommandCentre: public Rulling
	{
	public:
		CommandCentre(int radius = 0, int sub = 0, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) :Rulling(radius, sub, energy, slots, cost, coordinates) {}

		void moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector) override;
	};
}