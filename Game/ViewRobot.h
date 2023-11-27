#include "View.h"
#include "../Interfaces/Platform.h"

namespace Game
{
	class ViewRobot :public View
	{
	public:
		Robots::Platform* plt;
		ViewRobot(Robots::Platform* plt, std::string texture_name, sf::Vector2f scale, sf::Vector2f position, std::string message, std::string font_name, int character_size, sf::Color color, sf::Vector2f txt_pos) : plt(plt), View(texture_name, scale, position, message, font_name, character_size, color, txt_pos) {}

		void draw() override;
	};
}