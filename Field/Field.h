#include "Cell.h"
#include <unordered_map>
#pragma once
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

	struct nonConstCoordHash
	{
		std::size_t operator()(std::pair<int, int>& key)
		{
			return std::hash<int>()((key.first + key.second) * (key.first - key.second));
		}
	};

	struct CoordEqual
	{
		bool operator()(const std::pair<int, int>& key1, const std::pair<int, int>& key2) const
		{
			return (key1.first == key2.first) && (key1.second == key2.second);
		}
	};

	struct nonConstCoordEqual
	{
		bool operator()(std::pair<int, int>& key1, std::pair<int, int>& key2)
		{
			return (key1.first == key2.first) && (key1.second == key2.second);
		}
	};

	double distance(std::pair<int, int> cell1, std::pair<int, int> cell2);
	bool inArea(std::pair<int, int> centre, std::pair<int, int> cell, int radius);

	enum class RobotsTypes
	{
		CommandCentre,
		KamikazeRobot,
		MobilePlatform,
		QuantumPlatform,
		RobotCommander,
		RobotDestroyer,
		count
	};

	class Field
	{
	private:
		std::pair<int, int> size;
		std::unordered_map<std::pair<int, int>, Robots::Platform*, CoordHash, CoordEqual> platforms;
		std::vector<std::vector<Cell>> map;
		
		std::vector<std::vector<Cell>> createRandomMap(int width, int height);
	public:
		int total_poi=0;
		static int MAX_RANDOM_SIZE;
		static bool GROUND_MODE_ON;
		static int OBSTACLE_PERCENTAGE;

		Field(); //absolutely random field
		Field(int width, int height); //random field with fixed size
		Field(int width, int height, std::vector<std::vector<Cell>>& map, std::vector<Robots::Platform>& plt);
		/*~Field()
		{
			for (auto it : platforms)
			{
				if (it.second->isDynamic)
				{
					delete it.second;
				}
			}
		}*/

		int getWidth() { return size.first; }
		int getHeight() { return size.second; }
		std::pair<int, int> getSize() { return size; }
		Cell& getCellByCoordinates(std::pair<int, int> coordinates) { return map[coordinates.first][coordinates.second]; }
		Cell& getCellByCoordinates(int x, int y) { return map[x][y]; }
		std::vector<std::vector<Cell>>& getMap() { return map; }
		std::unordered_map<std::pair<int, int>, Robots::Platform*, CoordHash, CoordEqual>& getPlatforms() { return platforms; }
		
		Field& resize(int nwidth, int nheight);
		Field& resize(std::pair<int, int> nsize);

		void changeCellType(std::pair<int, int> coordinates, CellType ntype);
		void changeCellType(int x, int y, CellType ntype);

		void placePlatform(Robots::Platform* plt);
		void placeRandomPlatforms(int n);
		void erasePlatform(std::pair<int, int> coordinates);
		void erasePlatform(Robots::Platform* plt);
		//void erasePLatform(std::pair<int, int> coordinates, Robots::Platform* plt);
		void movePlatform(std::pair<int, int> coordinates, std::pair<int, int> vector);
		void destroyCell(std::pair<int, int> coordinates);
		void destroyArea(int radius, std::pair<int, int> centre);
		//std::vector<Cell> getPlatformReport(std::pair<int, int> coordinates, int ind);


		void consoleOutField(std::ostream& stream=std::cout);
		Robots::Platform* checkPlatformOnField(std::pair<int, int> coordinates);
		virtual void checkCoordinates(int x, int y);
		virtual void checkCoordinates(std::pair<int, int> coordinates);

		void cleanField();
	};
}