#include "../Field/Cell.h"

namespace Robots
{
	class Rulling
	{
	private:
		int subord;
		Platform* subordinates;
	public:
		Rulling(int sub);

		int getSub() { return subord; }
		Platform* getOrd() { return subordinates; }

		virtual Cell* getReport(int ind)=0;
		virtual void moveRobo(int ind, std::pair<int, int> vector)=0;
	};
}