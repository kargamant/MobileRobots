#include "Obstacle.h"

namespace Field
{
	class MovingObstacle :public Obstacle
	{
	private:
		int velocity;
		int radius;
		std::pair destination;
	public:
		MovingObstacle(int velocity, int radius, ObstacleType type, int cost, std::pair coordinates); //destination is random
		MovingObstacle(int velocity, int radius, Obstacle& obs);
		MovingObstacle(int velocity, int radius, std::pair dest, ObstacleType type, int cost, std::pair coordinates);
		MovingObstacle(int velocity, int radius, std::pair dest, Obstacle& obs);

		//random picking a destanation point in a certain radius and goes there with a constant speed
		void move();
	};
}