#include <SFML/Graphics.hpp>

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
		
		View(std::string texture_name, sf::Vector2f scale, sf::Vector2f position, std::string message, std::string font_name, int character_size, sf::Color color, sf::Vector2f txt_pos);

		~View()
		{
			delete texture;
		}

		virtual void draw()=0;
	};
}
