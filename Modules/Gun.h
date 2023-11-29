#include "../Field/Field.h"
#include "../Interfaces/Destroying.h"
#include "../Interfaces/Platform.h"
#pragma once

namespace Robots
{
	class Gun : public Module, public Destroying
	{
	private:
		Platform* motherboard;
		//int radius;
	public:
		Gun(Platform* motherboard=nullptr, double energy = 0, bool state = false, Priority priority = Priority::low, int cost = 0, int max_rad = 1) : motherboard(motherboard), Module(energy, state, priority, cost), Destroying(max_rad) {}

		void destroy(Field::Field* fld, std::pair<int, int> coordinates) override;
	
		Platform* getMom() { return motherboard; }
		//int getRange() { return radius; }
	};
}