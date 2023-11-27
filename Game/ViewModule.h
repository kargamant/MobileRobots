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
		std::pair<std::string, std::string> moduleToName(Robots::Module& mod);
	public:
		Robots::Module* mod;
		ViewModule(Robots::Module* mod, std::string texture_name, sf::Vector2f scale, sf::Vector2f position, std::string message, std::string font_name, int character_size, sf::Color color, sf::Vector2f txt_pos) : mod(mod), View(texture_name, scale, position, message, font_name, character_size, color, txt_pos) {}

		void draw() override;
	};
}