#include "Module.h"
#include "../Interfaces/Platform.h"
#include "EnergyGenerator.h"
#include "../utils/CheckComponent.h"
#include "Sensor.h"
#include "Gun.h"
#include "ManageModule.h"

namespace Robots
{

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

	std::string moduleToString(Module& mod)
	{
		if (isComponentCastable<Robots::Module&, Robots::EnergyGenerator&>(mod))
		{
			return "energy generator";
		}
		else if (isComponentCastable<Robots::Module&, Robots::Sensor&>(mod))
		{
			return "sensor";
		}
		else if (isComponentCastable<Robots::Module&, Robots::ManageModule&>(mod))
		{
			return "manage module";
		}
		else if (isComponentCastable<Robots::Module&, Robots::Gun&>(mod))
		{
			return "gun";
		}
	}
	
}