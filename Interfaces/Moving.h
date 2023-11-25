#include "Platform.h"
#include "../Field/Field.h"
#pragma once

namespace Robots
{
	class Moving 
	{
	private:
		int velocity; //cells per tick
	public:
		Moving(int velocity=1) :velocity(velocity){}

		int getVelocity() { return velocity; }
		Moving& setVelocity(int nvel) { velocity = nvel; return *this; }

		virtual void move(Field::Field* fld, std::pair<int, int> vector)=0;
	};
}