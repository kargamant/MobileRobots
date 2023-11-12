#include "Cell.h"
#include <unordered_map>
#include "../Interfaces/Platform.h"

namespace Field
{
	class Field
	{
	private:
		std::pair<int, int> size;
		std::unordered_map<Platform> platfroms; //all manage platforms
		Cell** map;
	public:
		Field(); //absolutely random field
		Field(int width, int height); //random field with fixed size
		Field(int width, int height, Cell** map, std::vector<Platform> plt);
		
		int getWidth() { return size.first; }
		int getHeight() { return size.second; }
		std::pair<int, int> getSize() { return size; }
		Cell& getCellByCoordinates(std::pair<int, int> coordinates) { return map[coordinates.first][coordinates.second]; }
		Cell& getCellByCoordinates(int x, int y) { return map[x][y]; }
		
		void resize(int nwidth, int nheight);
		void resize(std::pair<int, int> nsize);

		void changeCellType(std::pair<int, int> coordinates, Cell* ncell);
		void changeCellType(int x, int y, Cell* ncell);
	};
}