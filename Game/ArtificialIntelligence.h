#include "../Modules/ManageModule.h"

#include "../Field/Field.h"
#include "../Interfaces/Platform.h"
#include <limits>
#include <unordered_map>
#include "Chunk.h"
#pragma once

namespace Robots
{
	struct Node
	{
		int f = std::numeric_limits<int>::max(); //f cost = h+g
		int g = std::numeric_limits<int>::max(); //g cost - cost to get from start
		int h = std::numeric_limits<int>::max(); //h cost - heuristic cost to get to end from this node
		Field::Cell* cell;
		Node* predecessor;
		std::vector<Node*> neighbours;
		bool isTraversable = true;
		bool isOpen = false;
		bool isClosed = false;

		Node(Field::Cell* cell=nullptr) :cell(cell), predecessor(nullptr) { if (cell->getType() == Field::CellType::obstacle) isTraversable = false; }
		~Node() = default;
		void calculateF() { f = g + h; }
		void consoleOut(std::ostream& stream);
	};
	class ArtificialIntelligence
	{
	private:
		std::unordered_map<std::pair<int, int>, std::vector<Field::Cell*>, Field::CoordHash, Field::CoordEqual> obstacles; //discovered obstacles
		std::unordered_map<std::pair<int, int>, std::vector<Field::Cell*>, Field::CoordHash, Field::CoordEqual> poi; //discovered points of interest
		std::unordered_map<std::pair<int, int>, Node, Field::CoordHash, Field::CoordEqual> graph;
		std::vector<std::vector<Field::Cell>> cloneMap;
		static const int MINIMUM_CHUNKABLE_FIELD_SIZE=3;
		int money;
		int points;
	public:
		ArtificialIntelligence() :obstacles(), poi(), money(20000) {}

		int getMoney() { return money; }
		int getPoints() { return points; }
		std::vector<std::vector<Field::Cell>>& getCloneMap() { return cloneMap; }
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

		std::string makeMove(Game::Chunk& chunk);
		std::vector<Game::Chunk> divideField(Field::Field& fld);
		std::vector<Node*> path(Field::Cell* from, Field::Cell* to, Field::Field& field);
	};
}