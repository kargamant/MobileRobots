#include <iostream>
#include <fstream>
#include <string>
#include <limits>


namespace Dialogue
{
	int menue(std::fstream& filename);
	int getOpt(int from = std::numeric_limits<int>::min(), int to = std::numeric_limits<int>::max());
	int getOpt(const char c);
	bool isArg(char** begin, char** end, const std::string& option);
	char* getArg(char** begin, char** end, const std::string& option);
}