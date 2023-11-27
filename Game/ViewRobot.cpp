#include "ViewRobot.h"

namespace Game
{
	void ViewRobot::draw()
	{
		description.setString(std::format("({}, {}) : {}", std::to_string(plt->getX()), std::to_string(plt->getY()), plt->getName()));
	}
}