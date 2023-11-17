#include "Field.h"
#include <time.h>

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

		size = std::pair<int, int>(std::rand() % MAX_RANDOM_SIZE, std::rand() % MAX_RANDOM_SIZE);
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
			platforms.insert({ it.getCoordinates(), it });
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

	void Field::checkCoordinates(int x, int y)
	{
		if (x >= size.first || x < 0 || y >= size.second || y < 0) throw std::invalid_argument("Error. Invalid coordinates for this field.");
	}

	void Field::checkCoordinates(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates.first, coordinates.second);
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

	void Field::consoleOutField(std::ostream& stream)
	{
		for (int i = 0; i < size.first; i++)
		{
			for (int j = 0; j < size.second; j++)
			{
				stream << "[" << CellTypeToChar(map[i][j].getType()) << "] ";

			}
			stream << std::endl;
		}
	}
}