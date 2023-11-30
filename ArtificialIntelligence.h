#include "Modules/ManageModule.h"

#include "Field/Field.h"
#include "Interfaces/Platform.h"

#include <unordered_map>
#pragma once

namespace Robots
{
	class ArtificialIntelligence
	{
	private:
		std::unordered_map<std::pair<int, int>, std::vector<Field::Cell*>, Field::CoordHash, Field::CoordEqual> obstacles; //discovered obstacles
		std::unordered_map<std::pair<int, int>, std::vector<Field::Cell*>, Field::CoordHash, Field::CoordEqual> poi; //discovered points of interest
		int money;
		int points;
	public:
		ArtificialIntelligence() :obstacles(), poi(), money(20000) {}

		int getMoney() { return money; }
		int getPoints() { return points; }

		ArtificialIntelligence& setMoney(int nmoney) 
		{ 
			if (nmoney >= 0) money = nmoney;
			else throw std::invalid_argument("Error. You cant afford it.");
			return *this; 
		}
		ArtificialIntelligence& setPoints(int npoints) { points = npoints; return *this; }

		ArtificialIntelligence& addPoint() { points++; return *this; }
		//std::vector<Cell*> find(Field* field);
	};
}