#include "Application.h"
#include <algorithm>

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

	void Application::updateGraphTraversity()
	{
		for (int i = 0; i < field.getWidth(); i++)
		{
			for (int j = 0; j < field.getHeight(); j++)
			{
				if (field.getCellByCoordinates(i, j).getType() == Field::CellType::ground) ai.getGraph()[{i, j}].isTraversable = true;
				else if (field.getCellByCoordinates(i, j).getType() == Field::CellType::obstacle) ai.getGraph()[{i, j}].isTraversable = false;
			}
		}
	}
	void Application::connectGraph()
	{
		for (std::vector<Field::Cell>& row1 : field.getMap())
		{
			for (Field::Cell& cell1 : row1)
			{
				if (cell1.getType() != Field::CellType::obstacle)
				{
					for (std::vector<Field::Cell>& row2: field.getMap())
					{
						for (Field::Cell& cell2 : row2)
						{
							if (cell1.getCoordinates() != cell2.getCoordinates() && cell2.getType()!=Field::CellType::obstacle)
							{
								auto pth = ai.path(&cell1, &cell2, field);
								std::reverse(pth.begin(), pth.end());
								if (pth.size() == 0)
								{
									std::cout << "cells: " << std::endl;
									ai.getGraph()[cell1.getCoordinates()].consoleOut();
									ai.getGraph()[cell2.getCoordinates()].consoleOut();
									field.consoleOutField();
									exit(0);
								}
								while(!pth[0]->isTraversable)
								{
									field.changeCellType(pth[0]->cell->getCoordinates(), Field::CellType::ground);
									updateGraphTraversity();
									ai.cleanPath(pth);
									pth = ai.path(&cell1, &cell2, field);
									std::reverse(pth.begin(), pth.end());
								}
								ai.cleanPath(pth);
							}
						}
					}

				}
			}
		}
	}

	void Application::play()
	{
		ai.find(field);
	}
}