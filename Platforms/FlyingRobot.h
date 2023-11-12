#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"

namespace Robots
{
	class FlyingRobot: public Platform, public Moving
	{
	public:
		FlyingRobot(int velocity, std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates);

		void move(std::pair<int, int> vector) override;
	};
}