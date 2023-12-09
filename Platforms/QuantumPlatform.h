#include "../Interfaces/Platform.h"
#include "../Field/Field.h"
#include <vector>

namespace Robots
{
	class QuantumPlatform : public Platform
	{
	private:
		int linkageRadius;
		int linked;
		std::vector<QuantumPlatform> platforms;
	public:
		QuantumPlatform(int linkageRadius = 1, std::string name = "c3po", double energy = 0, int slots = 3, int cost = 0, std::pair<int, int> coordinates = { 0, 0 }) : linkageRadius(linkageRadius), Platform(name, energy, slots, cost, coordinates) {}

		int getLinkRad() { return linkageRadius; }
		int getLinked() { return linked; }
		std::vector<QuantumPlatform> getLinkPlatforms() { return platforms; }

		QuantumPlatform& setLinkRad(int nrad) { linkageRadius = nrad; return *this; }

		void link(QuantumPlatform& platform);
		void teleport(Field::Field* fld, int ind); //teleport to ind platform
		void deleteModule(int ind) override;//delete from every linked platform
		//void placeModule(int ind, Module& mod) override;//place on every linked platform
		void placeModule(Module& mod) override;
	};
}