#include "../Field/Cell.h"
#include "Platform.h"

namespace Robots
{
	class Rulling : public Platform
	{
	private:
		int subord;
		Platform* subordinates;
	public:
		Rulling(int sub);

		int getSub() { return subord; }
		Platform* getOrd() { return subordinates; }

		virtual Cell* getReport(int ind);
		virtual void moveRobo(int ind, std::pair<int, int> vector);
	};
}