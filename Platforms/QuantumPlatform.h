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
		QuantumPlatform(int linkageRadius, std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates);

		int getLinkRad() { return linkageRadius; }
		int getLinked() { return linked; }
		QuantumPlatform* getLinkRad() { return platforms; }

		QuantumPlatform& setLinkRad(int nrad) { linkageRadius = nrad; return *this; }

		void link(QuantumPlatform& platform);
		void teleport(int ind); //teleport to ind platform
		void deleteModule(int ind) override;//delete from every linked platform
		void placeModule(int ind) override;//place on every linked platform
	};
}