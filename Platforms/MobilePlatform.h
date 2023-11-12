#include "../Interfaces/Platform.h"
#include "../Interfaces/Moving.h"

namespace Robots
{
	class MobilePlatform : public Platform, public Moving
	{
	public:
		MobilePlatform(int velocity, std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates);
		MobilePlatform(MobilePlatform& mp);

		void move(std::pair<int, int> vector) override;
	};
}