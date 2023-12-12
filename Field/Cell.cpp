#include "Cell.h"
#include <string>

namespace Field
{
	char CellTypeToChar(CellType type)
	{
		switch (type)
		{
		case CellType::ground:
			return 'g';
		case CellType::obstacle:
			return 'o';
		case CellType::pointOfInterest:
			return 'i';
		case CellType::unknown:
			return 'u';
		default:
			return '\0';
		}
	}

	int CellTypeToInt(CellType type)
	{
		switch (type)
		{
		case CellType::ground:
			return 1;
		case CellType::obstacle:
			return 2;
		case CellType::pointOfInterest:
			return 3;
		default:
			return -1;
		}
	}
	
	std::string CellTypeToString(CellType type)
	{
		switch (type)
		{
		case CellType::ground:
			return "ground";
		case CellType::obstacle:
			return "obstacle";
		case CellType::pointOfInterest:
			return "point of interest";
		case CellType::unknown:
			return "unknown";
		default:
			return "";
		}
	}
}