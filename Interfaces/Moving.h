#include "Platform.h"
#include "../Field/Field.h"
#pragma once

namespace Robots
{
	class Moving : virtual public Platform
	{
	private:
		int velocity; //cells per tick
	public:
		Moving(int velocity=0, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) :velocity(velocity), Platform(energy, slots, cost, coordinates) {}

		int getVelocity() { return velocity; }
		Moving& setVelocity(int nvel) { velocity = nvel; return *this; }

		virtual void move(std::pair<int, int> vector);
	};
}