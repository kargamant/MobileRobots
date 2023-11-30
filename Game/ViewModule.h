#include "View.h"
#include "../Modules/Module.h"
#include <string>
#pragma once

namespace Game
{
	class ViewModule :public View
	{
	private:
		static std::string ENERGY_GENERATOR_TEXTURE;
		static std::string SENSOR_TEXTURE;
		static std::string MANAGE_MODULE_TEXTURE;
		static std::string GUN_TEXTURE;
		static std::string INVENTORY_ITEM_TEXTURE;
		std::pair<std::string, std::string> moduleToName(Robots::Module& mod);
		std::string formModuleDescription(Robots::Module& mod);
	public:
		View inventoryView;
		ViewModule* supplier=nullptr;
		Robots::Module* mod;
		ViewModule(Robots::Module* mod, std::pair<int, int> position, std::string message, std::pair<int, int> txt_pos, sf::Vector2f scale = SPRITE_SCALE, std::string font_name = FONT_NAME, int character_size = CHARACTER_SIZE, sf::Color color = TEXT_COLOR) : mod(mod), inventoryView(INVENTORY_ITEM_TEXTURE, position, message, txt_pos), View(moduleToName(*mod).second, position, message, txt_pos, scale, font_name, character_size, color) { isModule = true; }

		void draw() override;
	};
}