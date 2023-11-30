#include "Module.h"
#include "../Interfaces/Platform.h"
#include "EnergyGenerator.h"

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

	Module& Module::turnOn()
	{
		if (supplier != nullptr)
		{
			dynamic_cast<EnergyGenerator*>(supplier)->turnOnModule(this);
		}
		else
		{
			throw std::invalid_argument("Error. Module is not connected to power.");
		}
		return *this;
	}

	Module& Module::turnOff()
	{
		if (supplier != nullptr)
		{
			dynamic_cast<EnergyGenerator*>(supplier)->turnOffModule(this);
		}
		else
		{
			state = false;
		}
		return *this;
	}
}