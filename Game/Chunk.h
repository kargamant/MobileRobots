#include "../Field/Field.h"

namespace Game
{
	//class wrapper above field
	class Chunk
	{
	private:
		Field::Field& fld;
		int xLeftBorder;
		int xRightBorder;
		int yLeftBorder;
		int yRightBorder;
	public:
		Chunk(int x_left_border, int y_left_border, int x_right_border, int y_right_border, Field::Field& fld) :xLeftBorder(x_left_border), yLeftBorder(y_left_border), xRightBorder(x_right_border), yRightBorder(y_right_border), fld(fld) {}

		void checkCoordinates(int x, int y);
		void checkCoordinates(std::pair<int, int> coordinates);

		void changeCellType(int x, int y, Field::CellType ntype);
		void changeCellType(std::pair<int, int> coordinates, Field::CellType ntype);
		void destroyCell(std::pair<int, int> coordinates);

		void placePlatform(Robots::Platform* plt);
		void erasePlatform(std::pair<int, int> coordinates);
		void erasePlatform(Robots::Platform* plt);
		void movePlatform(std::pair<int, int> coordinates, std::pair<int, int> vector);

		void consoleOut(std::ostream& stream);
	};
}