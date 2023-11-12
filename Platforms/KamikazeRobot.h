#include "../Interfaces/Platform.h"
#include "../Interfaces/Destroying.h"

namespace Robots
{
	class KamikazeRobot :public Platform, public Destroying
	{
	private:
		int max_radius;
	public:
		KamikazeRobot(int max_rad, std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates);

		int getMaxRadius() { return max_radius; }
		KamikazeRobot& setMaxRadius(int nrad) { max_radius = nrad; return *this; }

		void destroy(int radius) override;
	};
}