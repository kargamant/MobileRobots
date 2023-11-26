#include "Module.h"
#include "../Interfaces/Platform.h"

namespace Robots
{
	std::string priorityToString(Priority pr)
	{
		switch (pr)
		{
		case Priority::low:
			return "low priority";
		case Priority::medium:
			return "medium priority";
		case Priority::high:
			return "high priority";
		default:
			return "";
		}
	}
}