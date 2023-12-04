#include "Field/Field.h"
#include "ArtificialIntelligence.h"

namespace Field
{
	//class wrapper above field
	class Chunk
	{
	private:
		Field& fld;
		int xBorder;
		int yBorder;
	public:
		Chunk(int x_border, int y_border, Field& fld) :xBorder(x_border), yBorder(y_border), fld(fld) {}

		void checkCoordinates(int x, int y)
		{
			if (x > xBorder || x < 0 || y > yBorder || y < 0) throw std::invalid_argument("Error. Invalid coordinates for this field.");
		}
		void checkCoordinates(std::pair<int, int> coordinates)
		{
			checkCoordinates(coordinates.first, coordinates.second);
		}

		void changeCellType(int x, int y, CellType ntype)
		{
			checkCoordinates(x, y);
			fld.changeCellType(x, y, ntype);
		}

		void changeCellType(std::pair<int, int> coordinates, CellType ntype)
		{
			changeCellType(coordinates.first, coordinates.second, ntype);
		}
		

		void placePlatform(Robots::Platform* plt)
		{
			checkCoordinates(plt->getCoordinates());
			fld.placePlatform(plt);
		}

		void erasePlatform(std::pair<int, int> coordinates)
		{
			checkCoordinates(coordinates);
			fld.erasePlatform(coordinates);
		}


		void erasePlatform(Robots::Platform* plt)
		{
			checkCoordinates(plt->getCoordinates());
			fld.erasePlatform(plt);
		}
		
		void movePlatform(std::pair<int, int> coordinates, std::pair<int, int> vector)
		{
			checkCoordinates(coordinates);
			checkCoordinates(coordinates.first + vector.first, coordinates.second + vector.second);
			fld.movePlatform(coordinates, vector);
		}

		void destroyCell(std::pair<int, int> coordinates)
		{
			checkCoordinates(coordinates);
			fld.destroyCell(coordinates);
		}
	};
}