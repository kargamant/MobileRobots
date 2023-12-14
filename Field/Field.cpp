#include "Field.h"
#include "../Interfaces/Rulling.h"
#include <time.h>
#include "../Platforms/RobotCommander.h"
#include "../utils/CheckComponent.h"
#include "../Modules/Sensor.h"
#include <math.h>
#include "../Interfaces/Moving.h"
#include "../Platforms/KamikazeRobot.h"
#include "../Platforms/MobilePlatform.h"
#include "../Platforms/QuantumPlatform.h"
#include "../Platforms/RobotDestroyer.h"
#include "../Modules/EnergyGenerator.h"

namespace Field
{
	int Field::MAX_RANDOM_SIZE = 3;
	bool Field::GROUND_MODE_ON = false;
	int Field::OBSTACLE_PERCENTAGE = 20;
	std::vector<std::vector<Cell>> Field::createRandomMap(int width, int height)
	{

		int max_obstacles = (double)((size.first * size.second) * ((double)OBSTACLE_PERCENTAGE / (double)100));
		//std::cout << "max obstacles: " << max_obstacles << std::endl;
		//exit(0);
		//maybe do it more smart
		std::srand(time(NULL));
		std::vector<std::vector<Cell>> map;
		for (int i = 0; i < width; i++)
		{
			map.push_back(std::vector<Cell>());
			for (int j = 0; j < height; j++)
			{
				if (Field::Field::GROUND_MODE_ON)
				{
					map[i].push_back(Cell(i, j, CellType::ground));
				}
				else
				{
					CellType randType = CellType{ static_cast<CellType>(std::rand() % static_cast<int>(CellType::count)) };
					if (randType == CellType::obstacle && max_obstacles == 0) randType = CellType::ground;
					else if (randType == CellType::obstacle) max_obstacles--;
					map[i].push_back(Cell(i, j, randType));
					if (randType == CellType::pointOfInterest) total_poi++;
				}
			}
		}
		return map;
	}

	void Field::placeRandomPlatforms(int n)
	{
		std::srand(time(NULL));
		bool commander_placed = false;
		for (int i = 0; i < n; i++)
		{
			RobotsTypes type{std::rand()%static_cast<int>(RobotsTypes::count)};
			if (type == RobotsTypes::KamikazeRobot || type == RobotsTypes::QuantumPlatform) type = RobotsTypes::RobotDestroyer;
			else if ((type == RobotsTypes::RobotCommander || type == RobotsTypes::CommandCentre) && commander_placed) type = RobotsTypes::RobotDestroyer;
			Robots::Platform* plt;
			switch (type)
			{
			case RobotsTypes::CommandCentre:
				plt = new Robots::CommandCentre();
				dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().setRadius(std::max(size.first, size.second));
				commander_placed = true;
				break;
			case RobotsTypes::RobotCommander:
				plt = new Robots::RobotCommander(1);
				commander_placed = true;
				break;
			case RobotsTypes::KamikazeRobot:
				plt = new Robots::KamikazeRobot(std::rand() % size.first);
				break;
			case RobotsTypes::MobilePlatform:
				plt = new Robots::MobilePlatform(1);
				break;
			case RobotsTypes::QuantumPlatform:
				plt = new Robots::QuantumPlatform();
				break;
			case RobotsTypes::RobotDestroyer:
				plt = new Robots::RobotDestroyer(2);
				break;
			}
			std::cout << plt->getName() << " " << (int)type << std::endl;
			Robots::EnergyGenerator* eg = new Robots::EnergyGenerator();
			plt->placeModule(*eg);
			if (type != RobotsTypes::MobilePlatform)
			{
				dynamic_cast<Robots::EnergyGenerator*>(plt->getRobo()[1])->connect(*plt->getRobo()[0]);
				plt->getRobo()[0]->turnOn();
			}
			if(!plt->getIsMaster())
			{
				Robots::Sensor* sens = new Robots::Sensor();
				plt->placeModule(*sens);
				if (type != RobotsTypes::MobilePlatform)
				{
					dynamic_cast<Robots::EnergyGenerator*>(plt->getRobo()[1])->connect(*plt->getRobo()[2]);
					plt->getRobo()[2]->turnOn();
				}
				else
				{
					dynamic_cast<Robots::EnergyGenerator*>(plt->getRobo()[0])->connect(*plt->getRobo()[1]);
					plt->getRobo()[1]->turnOn();
				}
			}
			bool correctlyPlaced = false;
			while (!correctlyPlaced)
			{
				try
				{
					int rand_x = std::rand() % size.first;
					int rand_y = std::rand() % size.second;
					plt->setCoordinates(rand_x, rand_y);
					plt->isDynamic = true;
					placePlatform(plt);
				}
				catch (std::invalid_argument)
				{
					continue;
				}
				correctlyPlaced = true;
			}
			
		}
		if (!commander_placed)
		{
			Robots::Platform* pt = new Robots::RobotCommander(1);
			Robots::EnergyGenerator* eg = new Robots::EnergyGenerator();
			pt->placeModule(*eg);
			dynamic_cast<Robots::EnergyGenerator*>(pt->getRobo()[1])->connect(*pt->getRobo()[0]);
			pt->getRobo()[0]->turnOn();

			commander_placed = true;
			bool correctlyPlaced = false;
			while (!correctlyPlaced)
			{
				try
				{
					pt->setCoordinates(std::rand() % size.first, std::rand() % size.second);
				}
				catch (std::invalid_argument)
				{
					continue;
				}
				correctlyPlaced = true;
			}
			pt->isDynamic = true;
			placePlatform(pt);
		}
	}

	Field::Field()
	{
		std::srand(time(NULL));

		size = std::pair<int, int>(5+std::rand() % MAX_RANDOM_SIZE, 5+std::rand() % MAX_RANDOM_SIZE);
		map = createRandomMap(size.first, size.second);
	}

	Field::Field(int width, int height):size(std::pair<int, int>(width, height))
	{
		map = createRandomMap(size.first, size.second);
	}

	Field::Field(int width, int height, std::vector<std::vector<Cell>>& map, std::vector<Robots::Platform>& plt):size(std::pair<int, int>(width, height)), map(map)
	{
		for (Robots::Platform& it : plt)
		{
			placePlatform(&it);
		}
	}

	Field& Field::resize(int nwidth, int nheight)
	{
		int width = getWidth();
		int height = getHeight();
		map.resize(nwidth);
		for (int i = 0; i < nwidth; i++) map[i].resize(nheight);
		if (nwidth > width && nheight > height)
		{
			std::vector<std::vector<Cell>> dWnH = createRandomMap(nwidth - width, nheight);
			std::vector<std::vector<Cell>> dHW = createRandomMap(width, nheight - height);
			for (int i = 0; i < width; i++)
			{
				for (int j = height; j < nheight; j++)
				{
					map[i].push_back(dHW[i][j-height]);
				}
			}
			for (int i = width; i < nwidth; i++)
			{
				map[i] = dWnH[i-width];
			}
		}
		else if (nwidth > width && nheight < height)
		{
			std::vector<std::vector<Cell>> nWdH = createRandomMap(nwidth - width, nheight);
			for (int i = width; i < nwidth; i++) map[i] = nWdH[i-width];
		}
		else if (nwidth<width && nheight>height)
		{
			std::vector<std::vector<Cell>> dWnH = createRandomMap(nwidth, nheight - height);
			for (int i = 0; i < nwidth; i++)
			{
				for (int j = height; j < nheight; j++) map[i].push_back(dWnH[i][j - height]);
			}
		}
		size.first = nwidth;
		size.second = nheight;
		return *this;
	}

	Field& Field::resize(std::pair<int, int> nsize)
	{
		return resize(nsize.first, nsize.second);
	}

	void Field::changeCellType(int x, int y, CellType ntype)
	{
		checkCoordinates(x, y);
		getCellByCoordinates(x, y).setType(ntype);
	}

	void Field::changeCellType(std::pair<int, int> coordinates, CellType ntype)
	{
		checkCoordinates(coordinates);
		getCellByCoordinates(coordinates).setType(ntype);
		if (ntype == CellType::pointOfInterest) total_poi++;
	}

	void Field::placePlatform(Robots::Platform* plt)
	{
		
		if (getCellByCoordinates(plt->getCoordinates()).getType() == CellType::pointOfInterest) total_poi--;
		if (checkPlatformOnField(plt->getCoordinates()) != nullptr)
		{
			throw std::invalid_argument("Error. There is platform on this cell.");
		}
		changeCellType(plt->getCoordinates(), CellType::ground);
		platforms.insert({plt->getCoordinates(), plt});
	}

	void Field::erasePlatform(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates);
		platforms.erase(coordinates);
	}

	void Field::erasePlatform(Robots::Platform* plt)
	{
		checkCoordinates(plt->getCoordinates());
		platforms.erase(plt->getCoordinates());
		/*for (auto it : platforms)
		{
			
			if (it.second == plt)
			{
				platforms.erase(it.first);
				break;
			}
		}*/
	}

	void Field::movePlatform(std::pair<int, int> coordinates, std::pair<int, int> vector)
	{
		if (checkPlatformOnField(coordinates) == nullptr) throw std::invalid_argument("Error. No platform with such coordinates on field.");

		Robots::Platform* plt = platforms[coordinates];

		if (!isComponentCastable<Robots::Platform*, Robots::Moving*>(plt)) throw std::invalid_argument("Error. This platform is not movable.");

		if (plt->getMaster() == nullptr && !plt->getIsMaster()) throw std::invalid_argument("Error. You cant move independently.");

		if (plt->getMaster() != nullptr && !inArea(plt->getMaster()->getCoordinates(), coordinates, dynamic_cast<Robots::CommandCentre*>(plt->getMaster())->getCpu().getRad()))
		{
			throw std::invalid_argument("Error. You cant go far from master robot.");
		}
		std::pair<int, int> destination = { coordinates.first + vector.first, coordinates.second + vector.second };
		
		checkCoordinates(destination);

		if (getCellByCoordinates(destination).getType() == CellType::pointOfInterest)
		{
			changeCellType(destination, CellType::ground);
			total_poi--;
		}
		if (getCellByCoordinates(destination).getType() == CellType::obstacle)
		{
			throw std::invalid_argument("Error. Cant go through obstacle.");
		}
		else if (checkPlatformOnField(destination) != nullptr)
		{
			throw std::invalid_argument("Error. Destination cell is your robot-mate.");
			/*
			* Gonna do it if there will be an ability to place many platforms on one cell
			*
			std::cout << "Go through platforms:" << std::endl;
			for (auto it : platforms)
			{
				std::cout << "{" << "(" << it.first.first << ", " << it.first.second << ")" << "; " << it.second->getName() << "}" << std::endl;
			}
			
			/*for (auto it : platforms)
			{
				std::cout << "{" << "(" << it.first.first << ", " << it.first.second << ")" << "; " << it.second->getName() << "}" << std::endl;
			}

			Robots::Platform* old_plt = checkPlatformOnField(destination);
			erasePlatform(old_plt);
			erasePlatform(plt);
			plt->setCoordinates(destination.first, destination.second);
			//std::cout << plt->getName() << std::endl;
			placePlatform(plt);
			std::cout << "old_plt:" << old_plt->getCoordinates().first << " " << old_plt->getCoordinates().second << old_plt->getName() << std::endl;
			placePlatform(old_plt);

			std::cout << "Go through platforms:" << std::endl;
			for (auto it : platforms)
			{
				std::cout << "{" << "(" << it.first.first << ", " << it.first.second << ")" << "; " << it.second->getName() << "}" << std::endl;
			}
			//std::cout << old_plt->getName() << std::endl;
			

			//std::cout << platforms[destination]->getName() << std::endl;
			*/
		}
		//TODO: add checking for obstacle and tracking points of interest
		else
		{
			//std::cout << (platforms[{getWidth()-1, 0}]==nullptr) << std::endl;
			
			erasePlatform(plt);
			plt->setCoordinates(destination.first, destination.second);
			placePlatform(plt);
			
			//std::cout << (checkPlatformOnField(coordinates) == nullptr) << std::endl;
		}
	}

	void Field::destroyCell(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates);
		Cell& target = getCellByCoordinates(coordinates);
		if (target.getType() == CellType::pointOfInterest) throw std::invalid_argument("Error. Cant destroy points of interest.");
		else if (checkPlatformOnField(target.getCoordinates()) != nullptr)
		{
			Robots::Platform* plt = checkPlatformOnField(target.getCoordinates());
			if (isComponentCastable<Robots::Platform&, Robots::Rulling&>(*plt))
			{
				for (Robots::Platform* sub : dynamic_cast<Robots::CommandCentre*>(plt)->getCpu().getSubOrd())
				{
					sub->setMaster(nullptr);
				}
				
			}
			erasePlatform(target.getCoordinates());
			
		}
		target.setType(CellType::ground);
	}

	void Field::destroyArea(int radius, std::pair<int, int> centre)
	{
		checkCoordinates(centre);
		std::pair<int, int> tlCorner = std::pair<int, int>(std::max(0, centre.first - radius), std::max(0, centre.second - radius));
		std::pair<int, int> brCorner = std::pair<int, int>(std::min(centre.first + radius, size.first), std::min(centre.second + radius, size.second));
		std::pair<int, int> it = tlCorner;
		while (true)
		{
			try
			{
				destroyCell(it);
			}
			catch (std::invalid_argument)
			{
				goto step;
			}
		step:
			if (it == brCorner)
			{
				break;
			}
			if (it.second != brCorner.second) it.second++;
			else
			{
				it.second = tlCorner.second;
				it.first++;
			}
		}

	}

	void Field::consoleOutField(std::ostream& stream)
	{
		for (int i = 0; i < size.first; i++)
		{
			for (int j = 0; j < size.second; j++)
			{
				if (auto search = platforms.find(std::pair<int, int>(i, j)); search != platforms.end()) stream << "[" << platforms[std::pair<int, int>(i, j)]->getName() << "] ";
				else stream << "[" << CellTypeToChar(map[i][j].getType()) << "] ";
			}
			stream << std::endl;
		}
	}

	//extra funcs
	void Field::checkCoordinates(int x, int y)
	{
		if (x >= size.first || x < 0 || y >= size.second || y < 0) throw std::invalid_argument("Error. Invalid coordinates for this field.");
	}

	void Field::checkCoordinates(std::pair<int, int> coordinates)
	{
		checkCoordinates(coordinates.first, coordinates.second);
	}

	Robots::Platform* Field::checkPlatformOnField(std::pair<int, int> coordinates)
	{
		if (platforms.find(coordinates) == platforms.end()) return nullptr;
		return  platforms[coordinates];
	}

	double distance(std::pair<int, int> cell1, std::pair<int, int> cell2)
	{
		return std::sqrt((cell1.first - cell2.first) * (cell1.first - cell2.first) + (cell1.second - cell2.second) * (cell1.second - cell2.second));
	}

	bool inArea(std::pair<int, int> centre, std::pair<int, int> cell, int radius)
	{
		return (std::abs(cell.first - centre.first) <= radius && std::abs(cell.second - centre.second) <= radius);
	}
}