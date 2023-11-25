#include "Platform.h"
#include "../Field/Field.h"
#pragma once

namespace Robots
{
	class Destroying
	{
	private:
		int max_radius;
	public:
		Destroying(int max_rad = 1) : max_radius(max_rad) {}
		
		int getMaxRadius() { return max_radius; }
		Destroying& setMaxRadius(int nrad) { max_radius = nrad; return *this; }
		
		//Can I pass a field via argument? Yes, but make it via method in field(destroyCell)
		virtual void destroy(Field::Field* fld, std::pair<int, int> coordinates)=0;
	};
}