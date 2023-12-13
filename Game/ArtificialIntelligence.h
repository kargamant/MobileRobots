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
		void consoleOut(std::ostream& stream=std::cout);
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
		ArtificialIntelligence() :obstacles(), poi(), money(20000), points(0) {}

		int getMoney() { return money; }
		int getPoints() { return points; }
		std::vector<std::vector<Field::Cell>>& getCloneMap() { return cloneMap; }
		std::unordered_map<std::pair<int, int>, Node, Field::CoordHash, Field::CoordEqual>& getGraph() { return graph; }

		ArtificialIntelligence& setGraph(std::unordered_map<std::pair<int, int>, Node, Field::CoordHash, Field::CoordEqual> ngraph) { graph = ngraph; return *this; }

		ArtificialIntelligence& setMoney(int nmoney) 
		{ 
			if (nmoney >= 0) money = nmoney;
			else throw std::invalid_argument("Error. You cant afford it.");
			return *this; 
		}
		ArtificialIntelligence& setPoints(int npoints) { points = npoints; return *this; }

		ArtificialIntelligence& addPoint() { points++; return *this; }
		
		void consoleOutGraph(std::ostream& stream);

		void find(Field::Field& fld, std::ostream& log = std::cout);
		std::string makeMove(Robots::Platform& plt, Field::Field& fld, std::vector<Field::Cell>& targets, std::pair<int, int> specific_target = {-1, -1});
		std::vector<Node*> path(Field::Cell* from, Field::Cell* to, Field::Field& field);
		void cleanPath(std::vector<Node*>& path);
		void cleanNode(Node* node);
		std::string masterSwitchTarget(Robots::Platform* plt, Robots::Platform* sub, Field::Field& fld);
		std::string goToTarget(Robots::Platform& plt, Field::Cell& target, Field::Field& fld);
	};
}