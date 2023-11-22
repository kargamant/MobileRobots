#include "Platform.h"
#include "../Field/Field.h"

namespace Robots
{
	int checkSensor(Platform* plt);

	class Rulling : virtual public Platform
	{
	private:
		int radius;
		int subord;
		std::vector<Platform> subordinates;
		void checkReachable(Field::Field* fld, int ind);
	public:
		Rulling(int radius=0, int sub = 0, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) : radius(radius), subord(sub), subordinates(std::vector<Platform>(subord)), Platform(energy, slots, cost, coordinates) {}

		int getSub() { return subord; }
		std::vector<Platform> getSubOrd() { return subordinates; }
		int getRadius() { return radius; }

		void subdue(Platform& plt);
		void release(int ind);

		void deleteModule(int ind) override;
		void placeModule(int ind, Module& mod) override;
		virtual std::vector<Field::Cell> getReport(Field::Field* fld, int ind);
		virtual void moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector);
		void checkInd(int ind);
	};
}