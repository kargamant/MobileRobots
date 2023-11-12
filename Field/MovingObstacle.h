#include "Obstacle.h"
#include "../Interfaces/Moving.h"

namespace Field
{
	class MovingObstacle :public Obstacle, public Moving 
	{
	private:
		int radius;
		std::pair<int, int> destination;
	public:
		MovingObstacle(int velocity, int radius, ObstacleType type, int cost, std::pair<int, int> coordinates); //destination is random
		MovingObstacle(int velocity, int radius, std::pair<int, int> dest, ObstacleType type, int cost, std::pair<int, int> coordinates);

		int getRadius() { return radius; }
		std::pair<int, int> getDestination() { return destination; }
		MovingObstacle& setRadius(int nradius) { radius = nradius; return *this; }
		MovingObstacle& setDestination(std::pair<int, int> ndest) { destination = ndest; return *this; }

		//random picking a destanation point in a certain radius and goes there with a constant speed
		void travel(); //uses move

		void move(std::pair<int, int> vector) override;
	};
}