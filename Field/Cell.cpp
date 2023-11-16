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
		case default:
			return '\0';
		}
	}
}