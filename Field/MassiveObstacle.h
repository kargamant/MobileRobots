#include "Obstacle.h"

namespace Field
{
	class MassiveObstacle
	{
	private:
		int radius;
		int cells;
		int cost; //for all obstacles to destroy
		Obstacle* obstacles;
	public:
		MassiveObstacle(); //random group of obstacles
		MassiveObstacle(Obstacle* obstacles, int cost);

		int getRadius() { return radius; }
		int getCells() { return cells; }
		int getCost() { return cost; }
		Obstacle* getObstacles() { return obstacles; }

		void destroy() { for (int i = 0; i < cells; i++) obstacles[i].destroy(); }
	};
}