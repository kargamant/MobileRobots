#include "Cell.h"

namespace Field
{
	//also should add a moving obstacle(animal)
	//massive obstacle(house or cave)
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

	};
}