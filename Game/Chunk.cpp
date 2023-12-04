#include "Chunk.h"

namespace Game
{
	/*Chunk& Chunk::operator=(Chunk&& chunk)
	{
		fld = chunk.fld;
		xLeftBorder = chunk.xLeftBorder;
		xRightBorder = chunk.xRightBorder;
		yLeftBorder = chunk.yLeftBorder;
		yRightBorder = chunk.yRightBorder;
	}*/

	void Chunk::checkCoordinates(int x, int y)
	{
		if (x > xRightBorder || x < xLeftBorder || y > yRightBorder || y < yLeftBorder) throw std::invalid_argument("Error. Invalid coordinates for this field.");
	}
	void Chunk::checkCoordinates(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates.first, coordinates.second);
	}

	void Chunk::changeCellType(int x, int y, Field::CellType ntype)
	{
		checkCoordinates(x, y);
		fld.changeCellType(x, y, ntype);
	}

	void Chunk::changeCellType(std::pair<int, int> coordinates, Field::CellType ntype)
	{
		changeCellType(coordinates.first, coordinates.second, ntype);
	}


	void Chunk::placePlatform(Robots::Platform* plt)
	{
		checkCoordinates(plt->getCoordinates());
		fld.placePlatform(plt);
	}

	void Chunk::erasePlatform(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates);
		fld.erasePlatform(coordinates);
	}


	void Chunk::erasePlatform(Robots::Platform* plt)
	{
		checkCoordinates(plt->getCoordinates());
		fld.erasePlatform(plt);
	}

	void Chunk::movePlatform(std::pair<int, int> coordinates, std::pair<int, int> vector)
	{
		checkCoordinates(coordinates);
		checkCoordinates(coordinates.first + vector.first, coordinates.second + vector.second);
		fld.movePlatform(coordinates, vector);
	}

	void Chunk::destroyCell(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates);
		fld.destroyCell(coordinates);
	}

	void Chunk::consoleOut(std::ostream& stream)
	{
		stream << "-------------------" << std::endl;
		stream << xLeftBorder << "<= x <=" << xRightBorder << std::endl;
		stream << yLeftBorder << "<= y <=" << yRightBorder << std::endl;
		for (int i = xLeftBorder; i <= xRightBorder; i++)
		{
			for (int j = yLeftBorder; j <= yRightBorder; j++)
			{
				if (auto search = fld.getPlatforms().find(std::pair<int, int>(i, j)); search != fld.getPlatforms().end()) stream << "[" << fld.getPlatforms()[std::pair<int, int>(i, j)]->getName() << "] ";
				else stream << "[" << Field::CellTypeToChar(fld.getMap()[i][j].getType()) << "] ";
			}
			stream << std::endl;
		}
		stream << "-------------------" << std::endl;
	}
}