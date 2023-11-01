#include "Obstacle.h"

namespace Field
{
	class MassiveObstacle
	{
	private:
		int radius;
		int cells;
		int cost;
		Obstacle* obstacles;
	public:
		MassiveObstacle();//random group of obstacles
		MassiveObstacle(Obstacle* obstacles);
		void destroy() { for (int i = 0; i < cells; i++) obstacles[i].destroy(); }
	};
}