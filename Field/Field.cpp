#include "Field.h"
#include "../Interfaces/Rulling.h"
#include <time.h>
#include "../Platforms/RobotCommander.h"
#include "../utils/CheckComponent.h"
#include "../Modules/Sensor.h"
#include <math.h>
#include "../Interfaces/Moving.h"
#include "../Platforms/KamikazeRobot.h"

namespace Field
{
	int Field::MAX_RANDOM_SIZE = 3;
	bool Field::GROUND_MODE_ON = false;
	std::vector<std::vector<Cell>> Field::createRandomMap(int width, int height)
	{
		//maybe do it more smart
		std::srand(time(NULL));
		std::vector<std::vector<Cell>> map;
		for (int i = 0; i < width; i++)
		{
			map.push_back(std::vector<Cell>());
			for (int j = 0; j < height; j++)
			{
				if (Field::Field::GROUND_MODE_ON)
				{
					map[i].push_back(Cell(i, j, CellType::ground));
				}
				else
				{
					CellType randType = CellType{ static_cast<CellType>(std::rand() % static_cast<int>(CellType::count)) };
					map[i].push_back(Cell(i, j, randType));
					if (randType == CellType::pointOfInterest) total_poi++;
				}
			}
		}
		return map;
	}

	Field::Field()
	{
		std::srand(time(NULL));

		size = std::pair<int, int>(5+std::rand() % MAX_RANDOM_SIZE, 5+std::rand() % MAX_RANDOM_SIZE);
		map = createRandomMap(size.first, size.second);
	}

	Field::Field(int width, int height):size(std::pair<int, int>(width, height))
	{
		map = createRandomMap(size.first, size.second);
	}

	Field::Field(int width, int height, std::vector<std::vector<Cell>> map, std::vector<Robots::Platform> plt):size(std::pair<int, int>(width, height)), map(map)
	{
		for (Robots::Platform& it : plt)
		{
			placePlatform(&it);
		}
	}

	void Field::resize(int nwidth, int nheight)
	{
		int width = getWidth();
		int height = getHeight();
		map.resize(nwidth);
		for (int i = 0; i < nwidth; i++) map[i].resize(nheight);
		if (nwidth > width && nheight > height)
		{
			std::vector<std::vector<Cell>> dWnH = createRandomMap(nwidth - width, nheight);
			std::vector<std::vector<Cell>> dHW = createRandomMap(width, nheight - height);
			for (int i = 0; i < width; i++)
			{
				for (int j = height; j < nheight; j++)
				{
					map[i].push_back(dHW[i][j-height]);
				}
			}
			for (int i = width; i < nwidth; i++)
			{
				map[i] = dWnH[i-width];
			}
		}
		else if (nwidth > width && nheight < height)
		{
			std::vector<std::vector<Cell>> nWdH = createRandomMap(nwidth - width, nheight);
			for (int i = width; i < nwidth; i++) map[i] = nWdH[i-width];
		}
		else if (nwidth<width && nheight>height)
		{
			std::vector<std::vector<Cell>> dWnH = createRandomMap(nwidth, nheight - height);
			for (int i = 0; i < nwidth; i++)
			{
				for (int j = height; j < nheight; j++) map[i].push_back(dWnH[i][j - height]);
			}
		}
		size.first = nwidth;
		size.second = nheight;
		
	}

	void Field::resize(std::pair<int, int> nsize)
	{
		resize(nsize.first, nsize.second);
	}

	void Field::changeCellType(int x, int y, CellType ntype)
	{
		checkCoordinates(x, y);
		getCellByCoordinates(x, y).setType(ntype);
	}

	void Field::changeCellType(std::pair<int, int> coordinates, CellType ntype)
	{
		checkCoordinates(coordinates);
		getCellByCoordinates(coordinates).setType(ntype);
	}

	void Field::placePlatform(Robots::Platform* plt)
	{
		if (getCellByCoordinates(plt->getCoordinates()).getType() == CellType::pointOfInterest) total_poi--;
		changeCellType(plt->getCoordinates(), CellType::ground);
		platforms.insert({plt->getCoordinates(), plt});
	}

	void Field::erasePlatform(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates);
		platforms.erase(coordinates);
	}

	void Field::erasePlatform(Robots::Platform* plt)
	{
		for (auto it = platforms.begin(); it != platforms.end();)
		{
			
			if (it->second == plt)
			{
				platforms.erase(it);
				break;
			}
			++it;
		}
	}

	void Field::movePlatform(std::pair<int, int> coordinates, std::pair<int, int> vector)
	{
		//std::cout << "db2" << std::endl;
		if (checkPlatformOnField(coordinates) == nullptr) throw std::invalid_argument("Error. No platform with such coordinates on field.");

		Robots::Platform* plt = platforms[coordinates];

		if (!isComponentCastable<Robots::Platform*, Robots::Moving*>(plt)) throw std::invalid_argument("Error. This platform is not movable.");

		if (plt->getMaster() != nullptr && !inArea(plt->getMaster()->getCoordinates(), coordinates, dynamic_cast<Robots::CommandCentre*>(plt->getMaster())->getCpu().getRad()))
		{
			throw std::invalid_argument("Error. You cant go far from master robot.");
		}
		std::pair<int, int> destination = { coordinates.first + vector.first, coordinates.second + vector.second };

		checkCoordinates(destination);

		if (getCellByCoordinates(destination).getType() == CellType::pointOfInterest)
		{
			changeCellType(destination, CellType::ground);
			total_poi--;
		}
		if (getCellByCoordinates(destination).getType() == CellType::obstacle)
		{
			throw std::invalid_argument("Error. Cant go through obstacle.");
		}
		else if (checkPlatformOnField(destination) != nullptr)
		{
			throw std::invalid_argument("Error. Destination cell is your robot-mate.");
			/*
			* Gonna do it if there will be an ability to place many platforms on one cell
			*
			std::cout << "Go through platforms:" << std::endl;
			for (auto it : platforms)
			{
				std::cout << "{" << "(" << it.first.first << ", " << it.first.second << ")" << "; " << it.second->getName() << "}" << std::endl;
			}
			
			/*for (auto it : platforms)
			{
				std::cout << "{" << "(" << it.first.first << ", " << it.first.second << ")" << "; " << it.second->getName() << "}" << std::endl;
			}

			Robots::Platform* old_plt = checkPlatformOnField(destination);
			erasePlatform(old_plt);
			erasePlatform(plt);
			plt->setCoordinates(destination.first, destination.second);
			//std::cout << plt->getName() << std::endl;
			placePlatform(plt);
			std::cout << "old_plt:" << old_plt->getCoordinates().first << " " << old_plt->getCoordinates().second << old_plt->getName() << std::endl;
			placePlatform(old_plt);

			std::cout << "Go through platforms:" << std::endl;
			for (auto it : platforms)
			{
				std::cout << "{" << "(" << it.first.first << ", " << it.first.second << ")" << "; " << it.second->getName() << "}" << std::endl;
			}
			//std::cout << old_plt->getName() << std::endl;
			

			//std::cout << platforms[destination]->getName() << std::endl;
			*/
		}
		//TODO: add checking for obstacle and tracking points of interest
		else
		{
			//std::cout << (platforms[{getWidth()-1, 0}]==nullptr) << std::endl;
			
			erasePlatform(plt);
			plt->setCoordinates(destination.first, destination.second);
			placePlatform(plt);
			
			//std::cout << (checkPlatformOnField(coordinates) == nullptr) << std::endl;
		}
	}

	void Field::destroyCell(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates);
		Cell& target = getCellByCoordinates(coordinates);
		if (target.getType() == CellType::pointOfInterest) throw std::invalid_argument("Error. Cant destroy points of interest.");
		else if (checkPlatformOnField(target.getCoordinates()) != nullptr)
		{
			Robots::Platform* plt = checkPlatformOnField(target.getCoordinates());
			if (isComponentCastable<Robots::Platform&, Robots::Rulling&>(*plt))
			{
				for (Robots::Platform* sub : dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd())
				{
					sub->setMaster(nullptr);
				}
				
			}
			erasePlatform(target.getCoordinates());
			
		}
		target.setType(CellType::ground);
	}

	void Field::destroyArea(int radius, std::pair<int, int> centre)
	{
		std::pair<int, int> tlCorner = std::pair<int, int>(std::max(0, centre.first - radius), std::max(0, centre.second - radius));
		std::pair<int, int> brCorner = std::pair<int, int>(std::min(centre.first + radius, size.first), std::min(centre.second + radius, size.second));
		std::pair<int, int> it = tlCorner;
		while (it != brCorner)
		{
			try
			{
				destroyCell(it);
			}
			catch (std::invalid_argument)
			{
				goto step;
			}
		step:
			if (it.second != brCorner.second) it.second++;
			else
			{
				it.second = tlCorner.second;
				it.first++;
			}
		}

	}

	void Field::consoleOutField(std::ostream& stream)
	{
		for (int i = 0; i < size.first; i++)
		{
			for (int j = 0; j < size.second; j++)
			{
				if (auto search = platforms.find(std::pair<int, int>(i, j)); search != platforms.end()) stream << "[" << platforms[std::pair<int, int>(i, j)]->getName() << "] ";
				else stream << "[" << CellTypeToChar(map[i][j].getType()) << "] ";
			}
			stream << std::endl;
		}
	}

	//extra funcs
	void Field::checkCoordinates(int x, int y)
	{
		if (x >= size.first || x < 0 || y >= size.second || y < 0) throw std::invalid_argument("Error. Invalid coordinates for this field.");
	}

	void Field::checkCoordinates(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates.first, coordinates.second);
	}

	Robots::Platform* Field::checkPlatformOnField(std::pair<int, int> coordinates)
	{
		//std::cout << "db2" << std::endl;
		if (platforms.find(coordinates) == platforms.end()) return nullptr;
		return  platforms[coordinates];
	}

	double distance(std::pair<int, int> cell1, std::pair<int, int> cell2)
	{
		return std::sqrt((cell1.first - cell2.first) * (cell1.first - cell2.first) + (cell1.second - cell2.second) * (cell1.second - cell2.second));
	}

	bool inArea(std::pair<int, int> centre, std::pair<int, int> cell, int radius)
	{
		return (std::abs(cell.first - centre.first) <= radius && std::abs(cell.second - centre.second) <= radius);
	}
}