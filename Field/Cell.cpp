#include "Cell.h"

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
}