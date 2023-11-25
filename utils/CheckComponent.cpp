#include "CheckComponent.h"
#include "Modules/Module.h"
#include "Modules/Sensor.h"

int foo()
{
	Robots::Module mod = Robots::Module();
	bool result = isComponentCastable<Robots::Module, Robots::Sensor>(mod);
}