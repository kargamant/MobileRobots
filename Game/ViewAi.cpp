#include "ViewAi.h"

namespace Game
{
	void ViewAi::draw()
	{
		sprite.setTexture(*texture);
		description.setString(formAiDescription());
	}

	std::string ViewAi::formAiDescription()
	{
		std::string out;
		out += "money: " + std::to_string(ai->getMoney()) + "\n";
		out += "points discovered: " + std::to_string(ai->getPoints()) + "\n";
		return out;
	}
}