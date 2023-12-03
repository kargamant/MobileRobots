#include "ArtificialIntelligence.h"
#include <format>

namespace Robots
{
	void ArtificialIntelligence::consoleOutGraph(std::ostream& stream)
	{
		stream << "key | node" << std::endl;
		for (auto it : graph)
		{
			auto key = it.first;
			auto value = it.second;

			stream << std::format("({}, {}) | ({}, {}) type: {} isTraversable: {}", std::to_string(key.first), std::to_string(key.second), std::to_string(value.cell.getCoordinates().first), std::to_string(value.cell.getCoordinates().second), Field::CellTypeToString(value.cell.getType()), value.isTraversable) << std::endl;
		}
	}
}