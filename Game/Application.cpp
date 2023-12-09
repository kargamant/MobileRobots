#include "Application.h"

namespace Game
{
	void Application::createGraph()
	{
		for (std::vector<Field::Cell>& row : field.getMap())
		{
			for (Field::Cell& cell : row)
			{
				Robots::Node node = Robots::Node(&cell);
				if (field.checkPlatformOnField(cell.getCoordinates()) != nullptr) node.isTraversable = false;
				ai.getGraph().insert({ cell.getCoordinates(), node });
			}
		}
	}

	void Application::play()
	{
		ai.find(field);
	}
}