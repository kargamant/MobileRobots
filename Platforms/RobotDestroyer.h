#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"
#include "../Interfaces/Destroying.h"

namespace Robots
{
	class RobotDestroyer : public Platform, public Moving, public Destroying
	{
		void move(std::pair<int, int> vector) override;
		void destroy(int radius) override;
		void deleteModule(int ind) override;
		void placeModule(int ind) override;
	};
}