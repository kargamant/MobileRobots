#include "View.h"
#include <string>

namespace Game
{
	class ViewModule :public View
	{
	private:
		static std::string ENERGY_GENERATOR_TEXTURE;
		static std::string SENSOR_TEXTURE;
		static std::string MANAGE_MODULE_TEXTURE;
		static std::string GUN_TEXTURE;
	public:
		std::pair<std::string, std::string> moduleToName(Robots::Module& mod);
		std::string formModuleDescription(Robots::Module& mod);
		View& inventoryView;
		Robots::Module* mod;
		ViewModule(Robots::Module* modfont_name, sf::Vector2f position, std::string message, sf::Vector2f txt_pos, sf::Vector2f scale = Drawer::SPRITE_SCALE, std::string font_name = Drawer::FONT_NAME, int character_size = Drawer::CHARACTER_SIZE, sf::Color color = sf::Color::White) : mod(mod), inventoryView(Drawer::INVENTORY_ITEM_TEXTURE, position, message, txt_pos), View(moduleToName(*mod).second, position, message, txt_pos, scale, font_name, character_size, color) {}

		void draw() override;
	};
}