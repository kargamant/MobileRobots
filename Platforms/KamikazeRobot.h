#include "../Interfaces/Platform.h"
#include "../Interfaces/Destroying.h"

namespace Robots
{
	class KamikazeRobot : public Destroying, public Platform
	{
	public:
		KamikazeRobot(int max_rad = 1, double energy = 0, int slots = 3, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) :Destroying(max_rad), Platform(energy, slots, cost, coordinates) { roboPriority = Priority::low; }

		void destroy(Field::Field* fld, std::pair<int, int> coordinates) override;
	};
}