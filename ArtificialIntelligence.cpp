#include "ArtificialIntelligence.h"
#include <format>
#include <queue>

namespace Robots
{
	void Node::consoleOut(std::ostream& stream)
	{
		stream << std::format("({}, {}) type: {} isTraversable: {}", std::to_string(cell->getX()), std::to_string(cell->getY()), Field::CellTypeToString(cell->getType()), isTraversable) << std::endl;
	}

	void ArtificialIntelligence::consoleOutGraph(std::ostream& stream)
	{
		stream << "key | node" << std::endl;
		for (auto it : graph)
		{
			auto key = it.first;
			auto value = it.second;

			stream << std::format("({}, {}) | ({}, {}) type: {} isTraversable: {}", std::to_string(key.first), std::to_string(key.second), std::to_string(value.cell->getCoordinates().first), std::to_string(value.cell->getCoordinates().second), Field::CellTypeToString(value.cell->getType()), value.isTraversable) << std::endl;
		}
	}

	std::vector<Node*> ArtificialIntelligence::path(Field::Cell* from, Field::Cell* to, Field::Field& field)
	{
		auto cmp = [](Node* first, Node* second) {return first->f > second->f; };
		std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openList(cmp);
		std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> closedList(cmp);
		std::vector<Node*> path;

		Node* start = &graph[from->getCoordinates()];
		Node* target = &graph[to->getCoordinates()];

		start->g = 0;
		start->h = Field::distance(from->getCoordinates(), to->getCoordinates());
		start->calculateF();
		openList.push(start);
		start->isOpen = true;

		while (!openList.empty())
		{
			//poping node with minimum f cost
			Node* current = openList.top();
			openList.pop();
			closedList.push(current);
			current->isOpen = false;
			current->isClosed = true;

			if (current == target)
			{
				Node* ptr = current;
				while (ptr != nullptr)
				{
					path.push_back(ptr);
					ptr = ptr->predecessor;
				}
				return path;
			}

			//generating neighbours
			if (current->cell->getX() - 1 >= 0)
			{
				Node* neighbour = &graph[{current->cell->getX() - 1, current->cell->getY()}];
				neighbour->g = current->g + 1;
				neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}
			if (current->cell->getX() + 1 < field.getWidth())
			{
				Node* neighbour = &graph[{current->cell->getX() + 1, current->cell->getY()}];
				neighbour->g = current->g + 1;
				neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}
			if (current->cell->getY() - 1 >= 0)
			{
				Node* neighbour = &graph[{current->cell->getX(), current->cell->getY()-1}];
				neighbour->g = current->g + 1;
				neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}
			if (current->cell->getY() + 1 < field.getHeight())
			{
				Node* neighbour = &graph[{current->cell->getX(), current->cell->getY()+1}];
				neighbour->g = current->g + 1;
				neighbour->h = Field::distance(neighbour->cell->getCoordinates(), to->getCoordinates());
				current->neighbours.push_back(neighbour);
			}

			for (Node* neighbour : current->neighbours)
			{
				if (!neighbour->isTraversable || neighbour->isClosed) continue;
				else
				{
					neighbour->predecessor = current;
					neighbour->calculateF();
					if (!neighbour->isOpen)
					{
						neighbour->isOpen = true;
						openList.push(neighbour);
					}
				}
			}
		}
		return path;
	}
}