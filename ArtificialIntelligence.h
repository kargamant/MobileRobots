#include "Modules/ManageModule.h"

#include "Field/Field.h"
#include "Interfaces/Platform.h"

#include <unordered_map>
#pragma once

namespace Robots
{
	struct Node
	{
		int f; //f cost = h+g
		int g; //g cost - cost to get from start
		int h; //h cost - heuristic cost to get to end from this node
		Field::Cell& cell;
		Node* predecessor;
		std::vector<Node*> neighbours;
		bool isTraversable = true;

		Node(Field::Cell& cell) :cell(cell), predecessor(nullptr) { if (cell.getType() == Field::CellType::obstacle) isTraversable = false; }
	};
	class ArtificialIntelligence
	{
	private:
		std::unordered_map<std::pair<int, int>, std::vector<Field::Cell*>, Field::CoordHash, Field::CoordEqual> obstacles; //discovered obstacles
		std::unordered_map<std::pair<int, int>, std::vector<Field::Cell*>, Field::CoordHash, Field::CoordEqual> poi; //discovered points of interest
		std::unordered_map<std::pair<int, int>, Node, Field::CoordHash, Field::CoordEqual> graph;
		int money;
		int points;
	public:
		ArtificialIntelligence() :obstacles(), poi(), money(20000) {}
		~ArtificialIntelligence()
		{
			for (auto it : graph)
			{
				for (auto neighbour : it.second.neighbours)
				{
					delete neighbour;
				}
			}
		}

		int getMoney() { return money; }
		int getPoints() { return points; }
		std::unordered_map<std::pair<int, int>, Node, Field::CoordHash, Field::CoordEqual>& getGraph() { return graph; }

		ArtificialIntelligence& setMoney(int nmoney) 
		{ 
			if (nmoney >= 0) money = nmoney;
			else throw std::invalid_argument("Error. You cant afford it.");
			return *this; 
		}
		ArtificialIntelligence& setPoints(int npoints) { points = npoints; return *this; }

		ArtificialIntelligence& addPoint() { points++; return *this; }
		
		void consoleOutGraph(std::ostream& stream);

		void find();
		std::string makeMove();
		std::vector<Field::Cell*> path(Field::Cell* from, Field::Cell* to);
	};
}