namespace Field
{
	enum class CellType
	{
		platform,
		obstacle,
		pointOfInterest
	};
	class Cell
	{
	private:
		std::pair coordinates;
		CellType type;
	public:
		Cell(std::pair coordinates);
		Cell(int x, int y);
		Cell(Cell& cell);

		std::pair getCoordinates() { return coordinates; }
		int getX() { return coordinates.first; }
		int getY() { return coordinates.second; }
		CellType getType() { return type; }

		Cell& setType(CellType ntype);

		//pure virtual methods
	};
}