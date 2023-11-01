#include "Cell.h"

namespace Field
{
	enum class ObstacleType
	{
		rock,
		tree,
		animal,
		house,
		cave
	};
	class Obstacle :public Cell
	{
	private:
		ObstacleType type;
		int cost; //cost to destroy an obstacle
		bool isDestroyed;
	public:
		Obstacle(ObstacleType type, int cost, std::pair coordinates);
		Obstacle(ObstacleType type, int cost, Cell& cell);
		Obstacle(Obstacle& obs);

		ObstacleType getType() { return type; }
		int getCost() { return cost; }


		void destroy() { isDestroyed = true; }
	};
}