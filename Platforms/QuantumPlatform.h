#include "Platform.h"

namespace Robots
{
	class QuantumPlatform : public Platform
	{
	private:
		bool quantumState;
		int radius;
	public:
		QuantumPlatform(bool quantumState, int radius, Platform& plt);

		void move(std::pair vector) override; //randomly teleports in a certain radius
	};
}