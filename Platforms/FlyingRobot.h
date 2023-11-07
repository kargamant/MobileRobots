#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"

namespace Robots
{
	class FlyingRobot
	{
	public:
		void move(std::pair<int, int> vector) override;
	};
}