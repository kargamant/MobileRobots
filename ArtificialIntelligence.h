#include "Platforms/ManageOverlay.h"
#include "Field/PointOfInterest.h"
#include "Field/Field.h"
using namespace Field;

namespace Robots
{
	class ArtificialIntelligence
	{
	private:
		int commanders;
		ManageOverlay* modules;
	public:
		ArtificialIntelligence(int commanders, ManageOverlay* modules);

		PointOfInterest* find(Field* field);
	};
}