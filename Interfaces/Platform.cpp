#include "Platform.h"
#include <time.h>
#include <iostream>

namespace Robots
{
	std::string Platform::NICKNAME_FILENAME = "base_nicknames.txt";

	std::string randomRoboName(std::fstream& file)
	{
		const std::string prefixes = "!@#$%^&*()_+";
		std::vector<std::string> base_nicknames;
		int i = 0;
		std::string to_read;
		while (!file.eof())
		{
			file >> to_read;
			base_nicknames.push_back(to_read);
			i++;
		}
		std::srand(time(NULL));
		i = std::rand() % i;
		int k = std::rand() % prefixes.length();

		//for (std::string& s : base_nicknames) std::cout << s << std::endl;
		//std::cout << base_nicknames[i]<<std::endl;
		return (base_nicknames[i]+ prefixes[k] + std::to_string((std::rand() % 10) * 1000));
	}

	Platform::Platform(double energy, int slots, int cost, std::pair<int, int> coordinates): energyLevel(energy), slots(slots), cost(cost), coordinates(coordinates), robo(new Module[slots])
	{
		std::fstream file;
		file.open("../"+NICKNAME_FILENAME, std::ios::in);
		name = randomRoboName(file);
		file.close();
	}
	Platform::Platform(std::string name, double energy, int slots, int cost, std::pair<int, int> coordinates) :energyLevel(energy), slots(slots), cost(cost), coordinates(coordinates), robo(new Module[slots]), name(name) {}
}