#include "Modules/ManageModule.h"
#include "Field/PointOfInterest.h"
#include "Field/Field.h"
#include "Interfaces/Platform.h"
#include "Field/Obstacle.h"
#include "Field/PointOfInterest.h"
#include <unordered_map>
using namespace Field;

namespace Robots
{
	class ArtificialIntelligence
	{
	private:
		std::unordered_map<Obstacle> obstacles; //discovered obstacles
		std::unordered_map<PointOfInterest> poi; //discovered points of interest
	public:
		ArtificialIntelligence();

		PointOfInterest* find(Field* field);
	};
}