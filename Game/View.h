#include <SFML/Graphics.hpp>
#include <format>
#pragma once

namespace Game
{
	class View
	{
	protected:
		static std::string FONT_NAME;
		static int CHARACTER_SIZE;
		static sf::Vector2f SPRITE_SCALE;
		static sf::Color TEXT_COLOR;
		static std::string RESOURCES_PATH;
		static std::string ROBOT_TEXTURE;
	public:
		sf::Sprite sprite;
		sf::Texture* texture;
		//sf::Vector2f scale;
		//sf::Vector2f position;
		sf::Font font;
		sf::Text description;
		
		View(std::string texture_name, std::pair<int, int> position, std::string message, std::pair<int, int> txt_pos, sf::Vector2f scale = SPRITE_SCALE, std::string font_name = FONT_NAME, int character_size = CHARACTER_SIZE, sf::Color color = TEXT_COLOR);

		/*~View()
		{
			delete texture;
		}*/

		virtual void draw();
	};
}
