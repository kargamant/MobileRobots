#include "Application.h"

namespace Game
{
	void Application::createGraph()
	{
		for (std::vector<Field::Cell>& row : field.getMap())
		{
			for (Field::Cell& cell : row)
			{
				Robots::Node node = Robots::Node(cell);				
				if (cell.getX() - 1 >= 0)
				{
					Robots::Node* neighbour = new Robots::Node(field.getCellByCoordinates(cell.getX() - 1, cell.getY()));
					node.neighbours.push_back(neighbour);
				}
				if (cell.getX() + 1 < field.getWidth())
				{
					Robots::Node* neighbour = new Robots::Node(field.getCellByCoordinates(cell.getX() + 1, cell.getY()));
					node.neighbours.push_back(neighbour);
				}
				if (cell.getY() - 1 >= 0)
				{
					Robots::Node* neighbour = new Robots::Node(field.getCellByCoordinates(cell.getX(), cell.getY() - 1));
					node.neighbours.push_back(neighbour);
				}
				if (cell.getY() + 1 < field.getHeight())
				{
					Robots::Node* neighbour = new Robots::Node(field.getCellByCoordinates(cell.getX(), cell.getY() + 1));
					node.neighbours.push_back(neighbour);
				}
				if (field.checkPlatformOnField(cell.getCoordinates()) != nullptr) node.isTraversable = false;
				ai.getGraph().insert({ cell.getCoordinates(), node });
			}
		}
	}
}