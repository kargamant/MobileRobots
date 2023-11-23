#include <utility>
#pragma once
namespace Field
{
	enum class CellType
	{
		ground,
		obstacle,
		pointOfInterest,
		count //just to track count of types if new ones will be added
	};

	char CellTypeToChar(CellType type);
	int CellTypeToInt(CellType type);

	class Cell
	{
	private:
		std::pair<int, int> coordinates;		
		CellType type;
	public:
		Cell(std::pair<int, int> coordinates=std::pair<int, int>(-1, -1), CellType type = CellType::ground) : coordinates(coordinates), type(type) {}
		Cell(int x, int y, CellType type=CellType::ground) : coordinates(std::pair<int, int>(x, y)), type(type) {}
		//Cell(Cell& cell) { coordinates = cell.coordinates; type = cell.type; }

		std::pair<int, int> getCoordinates() const { return coordinates; }
		int getX() const { return coordinates.first; }
		int getY() const { return coordinates.second; }
		CellType getType() const { return type; }

		Cell& setCoordinates(std::pair<int, int> ncoord) { coordinates = ncoord; return *this; }
		Cell& setX(int nx) { coordinates.first = nx; return *this; }
		Cell& setY(int ny) { coordinates.second = ny; return *this; }
		Cell& setType(CellType ntype) { type = ntype; return *this; }
	};
}