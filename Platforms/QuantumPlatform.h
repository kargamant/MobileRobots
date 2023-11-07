#include "../Interfaces/Platform.h"

namespace Robots
{
	class QuantumPlatform : public Platform
	{
	private:
		int linkageRadius;
		int linked;
		QuantumPlatform* platforms;
	public:
		QuantumPlatform(int linkageRadius);

		void link(QuantumPlatform& platform);
		void teleport(int ind);
		void deleteModule(int ind) override;
		void placeModule(int ind) override;
	};
}