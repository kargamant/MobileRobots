#include "Platform.h"
#include "ManageOverlay.h"

namespace Robots
{
	//robots are moving anyway, but platforms can stay still
	class CommandCentre: public Platform, public ManageOverlay
	{
	};
}