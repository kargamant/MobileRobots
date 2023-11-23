#pragma once
#include "dialogue/Menue.h"
#include "Interfaces/Platform.h"

namespace Dialogue
{
	int getMoney();
	Robots::Platform& createPlatform();
	void showPlatform(); //with certain coordinates
	void setModuleOnPlatform();
	void deleteModuleFromPlatform();



}