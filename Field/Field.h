#include "Cell.h"

namespace Field
{
	class Field
	{
	private:
		std::pair<int, int> size;
		Cell** map;
	public:
		Field(); //absolutely random field
		Field(int width, int height); //random field with fixed size
		
		int getWidth() { return size.first; }
		int getHeight() { return size.second; }
		std::pair getSize() { return size; }
		Cell& getCellByCoordinates(std::pair coordinates) { return map[coordinates.first][coordinates.second]; }
		Cell& getCellByCoordinates(int x, int y) { return map[x][y]; }
		
		void resize(int nwidth, int nheight);
		void resize(std::pair nsize);

		void changeCellType(std::pair coordinates, Cell& ncell);
		void changeCellType(int x, int y, Cell& ncell);
	};
}