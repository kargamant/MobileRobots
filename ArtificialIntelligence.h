#include "Modules/ManageModule.h"
#include "Field/PointOfInterest.h"
#include "Field/Field.h"
#include "Interfaces/Platform.h"
#include "Field/Obstacle.h"
#include "Field/PointOfInterest.h"
#include <unordered_map>

namespace Robots
{
	class ArtificialIntelligence
	{
	private:
		std::unordered_map<std::pair<int, int>, Field::Cell*> obstacles; //discovered obstacles
		std::unordered_map<std::pair<int, int>, Field::Cell*> poi; //discovered points of interest
	public:
		ArtificialIntelligence() :obstacles(), poi() {}

		//std::vector<Cell*> find(Field* field);
	};
}