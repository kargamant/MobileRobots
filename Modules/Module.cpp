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
		if (mod.isEnergyGenerator)
		{
			return "energy generator";
		}
		else if (mod.isSensor)
		{
			return "sensor";
		}
		else if (mod.isRulling)
		{
			return "manage module";
		}
		else if (mod.isGun)
		{
			return "gun";
		}
	}
	
}