#include "Field.h"
#include "../Interfaces/Rulling.h"
#include <time.h>
#include "../Platforms/RobotCommander.h"
#include "../CheckComponent.h"

namespace Field
{
	std::vector<std::vector<Cell>> createRandomMap(int width, int height)
	{
		//maybe do it more smart
		std::srand(time(NULL));
		std::vector<std::vector<Cell>> map;
		for (int i = 0; i < width; i++)
		{
			map.push_back(std::vector<Cell>());
			for (int j = 0; j < height; j++)
			{
				map[i].push_back(Cell(i, j, CellType{ static_cast<CellType>(std::rand() % static_cast<int>(CellType::count)) }));
				//map[i][j].setX(i).setY(j).setType(CellType{ std::rand() % static_cast<int>(CellType::count) });
			}
		}
		return map;
	}

	Field::Field()
	{
		//platfroms = std::unordered_map<std::pair<int, int>, Robots::Platform>();
		std::srand(time(NULL));

		size = std::pair<int, int>(5+ std::rand() % MAX_RANDOM_SIZE, 5+ std::rand() % MAX_RANDOM_SIZE);
		map = createRandomMap(size.first, size.second);
	}

	Field::Field(int width, int height):size(std::pair<int, int>(width, height))
	{
		//platfroms = std::unordered_map<std::pair<int, int>, Robots::Platform>();
		map = createRandomMap(size.first, size.second);
	}

	Field::Field(int width, int height, std::vector<std::vector<Cell>> map, std::vector<Robots::Platform> plt):size(std::pair<int, int>(width, height)), map(map)
	{
		//platfroms = std::unordered_map<std::pair<int, int>, Robots::Platform>();
		for (Robots::Platform& it : plt)
		{
			placePlatform(&it);
			//platforms[it.getCoordinates()] = it;
			//platforms.emplace(std::make_pair(it.getCoordinates(), it));
		}
	}

	void Field::resize(int nwidth, int nheight)
	{
		int width = getWidth();
		int height = getHeight();
		//maybe shouldn't resize and do it afterwards
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
		platforms.insert({plt->getCoordinates(), plt});
	}

	void Field::erasePlatform(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates);
		platforms.erase(coordinates);
	}

	void Field::movePlatform(std::pair<int, int> coordinates, std::pair<int, int> vector)
	{
		if (checkPlatformOnField(coordinates) == nullptr) throw std::invalid_argument("Error. No platform with such coordinates on field.");
		Robots::Platform* plt = platforms[coordinates];
		//TODO: add checking for obstacle and tracking points of interest
		if (!isComponentCastable<Robots::Platform*, Robots::Moving*>(plt)) throw std::invalid_argument("Error. This platform is not movable.");
		if (isComponentCastable<Robots::Platform*, Robots::RobotCommander*>(plt))
		{
			for (Robots::Platform& it : dynamic_cast<Robots::RobotCommander*>(plt)->getSubOrd())
			{
				try
				{
					movePlatform(it.getCoordinates(), vector);
				}
				catch (std::invalid_argument)
				{
					continue;
				}
			}
		}

		dynamic_cast<Robots::Moving*>(plt)->move(vector);
		erasePlatform(coordinates);
		placePlatform(dynamic_cast<Robots::Moving*>(plt));
	}

	/*std::vector<Cell> Field::getPlatformReport(std::pair<int, int> coordinates, int ind)
	{
		checkPlatformOnField(coordinates);

		Robots::Platform* subordinate = platforms[coordinates];

		//if (distance(rulling_coordinates, coordinates) > dynamic_cast<Robots::Rulling*>(ruller)->getRadius()) throw std::invalid_argument("Error. Robot is not reachable from rulling robot.");

		//int ind = checkSensor(platforms[coordinates]);
		//if (ind == -1) throw std::invalid_argument("Error. Platform with this coordinates has no sensor module on it. Report is impossible.");
		
		Robots::Module& sensor = subordinate->getRobo()[ind];
		return dynamic_cast<Robots::Sensor&>(sensor).scan(this);
	}*/



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

	/*bool isCommander(Robots::Platform* plt)
	{
		try
		{
			dynamic_cast<Robots::RobotCommander*>(plt);
		}
		catch (std::bad_cast)
		{
			return false;
		}
		return true;
	}

	void checkMoving(Robots::Platform* plt)
	{
		try
		{
			dynamic_cast<Robots::Moving*>(plt);
		}
		catch (std::bad_cast)
		{
			throw std::invalid_argument("Error. This platform is not movable.");
		}
	}

	void checkRulling(Robots::Platform* plt)
	{
		try
		{
			dynamic_cast<Robots::Rulling*>(plt);
		}
		catch (std::bad_cast)
		{
			throw std::invalid_argument("Error. This platform is not a commander, command centre or any other type of rulling entity.");
		}
	}*/

	Robots::Platform* Field::checkPlatformOnField(std::pair<int, int> coordinates)
	{
		if (platforms.find(coordinates) == platforms.end()) return nullptr;
		return  platforms[coordinates];
	}

	double Field::distance(std::pair<int, int> cell1, std::pair<int, int> cell2)
	{
		checkCoordinates(cell1);
		checkCoordinates(cell2);
		return std::sqrt((cell1.first - cell2.first) * (cell1.first - cell2.first) + (cell1.second - cell2.second) * (cell1.second - cell2.second));
	}

	double distance(std::pair<int, int> cell1, std::pair<int, int> cell2)
	{
		return std::sqrt((cell1.first - cell2.first) * (cell1.first - cell2.first) + (cell1.second - cell2.second) * (cell1.second - cell2.second));
	}
}