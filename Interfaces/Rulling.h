#include "../Field/Cell.h"

namespace Robots
{
	class Rulling
	{
	public:
		virtual Cell* getReport(int ind)=0;
		virtual void moveRobo(int ind, std::pair<int, int> vector)=0;
	};
}