#include "Cell.h"
#include <unordered_map>
#include "../Interfaces/Platform.h"
#include <iostream>

namespace Field
{
	Cell** createRandomMap(int width, int height);
	class Field
	{
	private:
		static int MAX_RANDOM_SIZE = 100;
		std::pair<int, int> size;
		std::unordered_map<std::pair<int, int>, Robots::Platform> platfroms; //all manage platforms
		std::vector<std::vector<Cell>> map;
		void checkCoordinates(int x, int y);
		void checkCoordinates(std::pair<int, int> coordinates);
	public:
		static void changeMaxRandomSize(int nsize) { MAX_RANDOM_SIZE = nsize; }
		Field(); //absolutely random field
		Field(int width, int height); //random field with fixed size
		Field(int width, int height, Cell** map, std::vector<Robots::Platform> plt);
		
		int getWidth() { return size.first; }
		int getHeight() { return size.second; }
		std::pair<int, int> getSize() { return size; }
		Cell& getCellByCoordinates(std::pair<int, int> coordinates) { return map[coordinates.first][coordinates.second]; }
		Cell& getCellByCoordinates(int x, int y) { return map[x][y]; }
		
		void resize(int nwidth, int nheight);
		void resize(std::pair<int, int> nsize);

		void changeCellType(std::pair<int, int> coordinates, CellType ntype);
		void changeCellType(int x, int y, CellType ntype);

		void consoleOutField(std::ostream& stream=std::cout);
	};
}