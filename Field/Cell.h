namespace Field
{
	enum class CellType
	{
		ground,
		obstacle,
		pointOfInterest
	};
	class Cell
	{
	private:
		std::pair<int, int> coordinates;		
		CellType type;
	public:
		Cell(std::pair<int, int> coordinates, CellType type=CellType::ground) : this->coordinates(coordinates), this->type(type) {}
		Cell(int x, int y, CellType type=CellType::ground) : coordinates(std::pair<int, int>(x, y)), this->type(type) {}
		Cell(Cell& cell) { coordinates = cell.coordinates; type = cell.type; }

		std::pair<int, int> getCoordinates() { return coordinates; }
		int getX() { return coordinates.first; }
		int getY() { return coordinates.second; }
		CellType getType() { return type; }

		Cell& setType(CellType ntype) { type = ntype; return *this; };
	};
}