#include "../Interfaces/Platform.h"
#include "../Interfaces/Rulling.h"

namespace Robots
{
	//robots are moving anyway, but platforms can stay still
	class CommandCentre: public Platform, public Rulling
	{
	public:
		CommandCentre(int sub, std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates);
		CommandCentre(int sub, Platform& plt);

		void moveRobo(int ind, std::pair<int, int> vector) override;
		Cell* getReport(int ind) override;
		void deleteModule(int ind) override;
		void placeModule(int ind) override;
	};
}