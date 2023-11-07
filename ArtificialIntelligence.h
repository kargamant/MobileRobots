#include "Modules/ManageModule.h"
#include "Field/PointOfInterest.h"
#include "Field/Field.h"
#include "Interfaces/Platform.h"
#include <unordered_map>
using namespace Field;

namespace Robots
{
	class ArtificialIntelligence
	{
	private:
		int commanders;
		ManageModule* modules;
		std::unordered_map<Platform> map;
	public:
		ArtificialIntelligence(int commanders, ManageOverlay* modules);

		PointOfInterest* find(Field* field);
	};
}