#include "Obstacle.h"

namespace Field
{
	class MassiveObstacle
	{
	private:
		int radius;
		int cells;
		Obstacle* obstacles;
	public:
		MassiveObstacle();//random group of obstacles
		MassiveObstacle(Obstacle* obstacles);
	};
}