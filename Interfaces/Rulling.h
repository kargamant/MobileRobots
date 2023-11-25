#include "Platform.h"
#include "../Field/Field.h"
#pragma once

namespace Robots
{
	int checkSensor(Platform* plt);

	class Rulling 
	{
	private:
		int radius; //radius of control
	public:
		Rulling(int radius=0) : radius(radius) {}

		int getRadius() { return radius; }

		virtual std::vector<Field::Cell> getReport(Field::Field* fld, int ind)=0;
		virtual void moveRobo(Field::Field* fld, int ind, std::pair<int, int> vector)=0;
		//virtual void subdue(Platform& plt) = 0;
		//virtual void release(int ind) = 0;
	};
}