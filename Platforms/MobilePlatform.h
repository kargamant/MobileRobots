#include "../Interfaces/Moving.h"
#pragma once

namespace Robots
{
	class MobilePlatform : public Moving
	{
	public:
		MobilePlatform(int velocity = 0, std::string name = std::string("c3po"), double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)):Moving(velocity, name, energy, slots, cost, coordinates);

		void move(std::pair<int, int> vector) override;
	};
}