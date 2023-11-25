#include "../Interfaces/Platform.h"
#include "../Interfaces/Destroying.h"

namespace Robots
{
	class KamikazeRobot : public Destroying, public Platform
	{
	public:
		KamikazeRobot(int max_rad = 1, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) :Destroying(max_rad), Platform(energy, slots, cost, coordinates) {}

		int getMaxRadius() { return max_radius; }
		KamikazeRobot& setMaxRadius(int nrad) { max_radius = nrad; return *this; }

		void destroy(Field::Field* fld, std::pair<int, int> coordinates) override;
	};
}