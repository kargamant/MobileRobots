#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"
#include "../Interfaces/Destroying.h"

namespace Robots
{
	class RobotDestroyer : public Moving, public Destroying, public Platform
	{
	public:
		RobotDestroyer(max_radius = 0, int velocity = 0, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0));

		void move(std::pair<int, int> vector) override;
		void destroy(Field::Field* fld, std::pair<int, int> coordinates) override;
		void deleteModule(int ind) override;
		void placeModule(int ind) override;
	};
}