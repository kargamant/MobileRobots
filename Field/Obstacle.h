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
		ObstacleType obsType;
		int cost; //cost to destroy an obstacle
		bool isDestroyed;
	public:
		Obstacle(ObstacleType type, int cost, std::pair<int, int> coordinates) :obsType(type), cost(cost), isDestroyed(false), Cell(coordinates, CellType::obstacle) {}

		ObstacleType getObsType() { return type; }
		int getCost() { return cost; }
		bool isDestroyed() { return isDestroyed; }
		Obstacle& setObsType(ObstacleType ntype) { type = ntype; return *this; }
		Obstacle& setCost(int ncost) { cost = ncost; return *this; }

		void destroy() { isDestroyed = true; }
	};
}