#include "Platform.h"

namespace Robots
{
	class MobilePlatform : public Platform
	{
	private:
		int velocity;
	public:
		MobilePlatform(int velocity, std::string name, double energy, int slots, int cost, std::pair coordinates);
		MobilePlatform(int velocity, Platform& plt);
		MobilePlatform(MobilePlatform& mp);

		void move(std::pair vector);
	};
}