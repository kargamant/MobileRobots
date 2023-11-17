#include "Cell.h"
#include <unordered_map>
#include <utility>
#include <vector>
#include "../Interfaces/Platform.h"
#include <iostream>

namespace Field
{
	struct CoordHash
	{
		std::size_t operator()(const std::pair<int, int>& key) const
		{
			return std::hash<int>()((key.first + key.second)* (key.first - key.second));
		}
	};

	struct CoordEqual
	{
		bool operator()(const std::pair<int, int>& key1, const std::pair<int, int>& key2) const
		{
			return (key1.first == key2.first) && (key1.second == key2.second);
		}
	};
	
	std::vector<std::vector<Cell>> createRandomMap(int width, int height);
	class Field
	{
	private:
		std::pair<int, int> size;
		std::unordered_map<std::pair<int, int>, Robots::Platform&, CoordHash, CoordEqual> platforms; //all manage platforms
		std::vector<std::vector<Cell>> map;
		void checkCoordinates(int x, int y);
		void checkCoordinates(std::pair<int, int> coordinates);
	public:
		static int MAX_RANDOM_SIZE;
		//void changeMaxRandomSize(int nsize) { MAX_RANDOM_SIZE = nsize; }
		Field(); //absolutely random field
		Field(int width, int height); //random field with fixed size
		Field(int width, int height, std::vector<std::vector<Cell>> map, std::vector<Robots::Platform> plt);
		
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