#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"
#include "../Interfaces/Destroying.h"

namespace Robots
{
	class RobotDestroyer : public Platform, public Moving, public Destroying
	{
	public:
		RobotDestroyer(std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates, int velocity);

		void move(std::pair<int, int> vector) override;
		void destroy(int radius) override;
		void deleteModule(int ind) override;
		void placeModule(int ind) override;
	};
}