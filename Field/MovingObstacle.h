#include "Obstacle.h"

namespace Field
{
	class MovingObstacle :public Obstacle
	{
	private:
		int velocity;
		int radius;
		std::pair destanation;
	public:
		MovingObstacle(int velocity, int radius); //destination is random
		MovingObstacle(int velocity, int radius, std::pair dest);

		//random picking a destanation point in a certain radius and goes there with a constant speed
		void move();
	};
}