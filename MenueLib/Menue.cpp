#include "Menue.h"


namespace Dialogue
{
	bool isArg(char** begin, char** end, const std::string& option)
	{
		char** p = begin;
		while (p != end)
		{
			if (*p == option) return true;
			++p;
		}
		return false;
	}

	char* getArg(char** begin, char** end, const std::string& option)
	{
		char** p = begin;
		while (p != end)
		{
			if (*p == option) return *(++p);
			++p;
		}
		return nullptr;
	}

	int menue(std::fstream& file)
	{
		int k = 0;
		std::string line;
		while (!file.eof())
		{
			std::getline(file, line);
			std::cout << line<<std::endl;
			k++;
		}
		return k - 2;
	}

	int getOpt(int from, int to)
	{
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		int opt;
		do
		{
			std::cin >> opt;
			if (std::cin.eof())
			{
				throw std::runtime_error("EOF. Programm end.");
			}
			else if (std::cin.bad())
			{
				throw std::runtime_error("Error. Unfixable crash. Programm stopped.");
			}
			else if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Error. Wrong format. Try again." << std::endl;
				continue;
			}
			else if (opt < from || opt>to)
			{
				std::cout << "Error. Option can only be from " << from << " to " << to << ". Try again." << std::endl;
				continue;
			}
			else break;
		} while (1);

		//std::cin.clear();
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return opt;
	}

	int getOpt(char c)
	{
		char opt;
		do
		{
			std::cin >> opt;
			if (std::cin.eof())
			{
				throw std::runtime_error("EOF. Programm end.");
			}
			else if (std::cin.bad())
			{
				throw std::runtime_error("Error. Unfixable crash. Programm stopped.");
			}
			else if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Error. Wrong format. Try again." << std::endl;
				continue;
			}
			else break;
		} while (1);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
}