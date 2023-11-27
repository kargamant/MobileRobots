#include <SFML/Graphics.hpp>
#include "Drawer.h"

namespace Game
{
	class View
	{
	protected:
		static std::string RESOURCES_PATH;
	public:
		sf::Sprite sprite;
		sf::Texture* texture;
		//sf::Vector2f scale;
		//sf::Vector2f position;
		sf::Font font;
		sf::Text description;
		
		View(std::string texture_name, sf::Vector2f position, std::string message, sf::Vector2f txt_pos, sf::Vector2f scale=Drawer::SPRITE_SCALE, std::string font_name=Drawer::FONT_NAME, int character_size=Drawer::CHARACTER_SIZE, sf::Color color=sf::Color::White);

		~View()
		{
			delete texture;
		}

		virtual void draw();
	};
}
