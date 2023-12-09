#include "../Interfaces/Moving.h"
#pragma once

namespace Robots
{
	class MobilePlatform : public Moving, public Platform
	{
	public:
		MobilePlatform(int velocity = 0, std::string name = std::string("c3po"), double energy = 0, int slots = 3, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) :Moving(velocity), Platform(name, energy, slots, cost, coordinates) {}
		
		void move(Field::Field* fld, std::pair<int, int> vector) override;
	};
}