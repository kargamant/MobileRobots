#include "View.h"
#include "../Interfaces/Platform.h"
#include "ViewModule.h"
#include "../Field/Field.h"
#pragma once

namespace Game
{
	//freddy ur ur ur
	class ViewRobot :public View
	{
	private:
		Field::Field* field;
		std::string formRobotDescription(Robots::Platform& plt);
	public:
		Robots::Platform* plt;
		std::vector<std::pair<ViewModule&, ViewModule&>> modules;
		ViewRobot(Robots::Platform* plt, Field::Field* field, std::pair<int, int> position, std::string message, std::pair<int, int> txt_pos, sf::Vector2f scale = SPRITE_SCALE, std::string font_name = FONT_NAME, int character_size = CHARACTER_SIZE, sf::Color color = TEXT_COLOR) : plt(plt), field(field), View(ROBOT_TEXTURE, position, message, txt_pos, scale, font_name, character_size, color) {}

		void draw() override;
		void drawModuleBar();
	};
}