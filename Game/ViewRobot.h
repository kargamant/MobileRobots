#include "View.h"
#include "../Interfaces/Platform.h"

namespace Game
{
	class ViewRobot :public View
	{
	private:
		Field::Field* field;
	public:
		Robots::Platform* plt;
		std::vector<std::pair<ViewModule&, ViewModule&>> modules;
		ViewRobot(Robots::Platform* plt, Field::Field* field, sf::Vector2f position, std::string message, sf::Vector2f txt_pos, sf::Vector2f scale = Drawer::SPRITE_SCALE, std::string font_name = Drawer::FONT_NAME, int character_size = Drawer::CHARACTER_SIZE, sf::Color color = sf::Color::White) : plt(plt), field(field), View(Drawer::ROBOT_TEXTURE, position, message, txt_pos, scale, font_name, character_size, color) {}

		void draw() override;
		void drawModuleBar();
	};
}