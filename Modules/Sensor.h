#include "Module.h"
#include "Cell.h"

namespace Robots
{
	class Sensor :public Module
	{
	private:
		int radius;
		std::pair direction; //vector from current position to destination point
		int angle;
	public:
		Cell* scan();
	};
}