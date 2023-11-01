#include "Platform.h"

namespace Robots
{
	class MobilePlatform : public Platform
	{
	private:
		int velocity;
	public:
		void move(std::pair vector);
	};
}