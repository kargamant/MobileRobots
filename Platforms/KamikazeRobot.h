#include "../Interfaces/Platform.h"
#include "../Interfaces/Destroying.h"

namespace Robots
{
	class KamikazeRobot :public Platform, public Destroying
	{
	private:
		int max_radius;
	public:
		void destroy(int radius) override;
		void deleteModule(int ind) override;
		void placeModule(int ind) override;
	};
}