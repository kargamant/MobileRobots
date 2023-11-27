#include "View.h"

namespace Game
{



	View::View(std::string texture_name, sf::Vector2f position, std::string message, sf::Vector2f txt_pos, sf::Vector2f scale, std::string font_name, int character_size, sf::Color color)
	{
		texture = new sf::Texture();
		texture->loadFromFile(RESOURCES_PATH + "/" + texture_name);
		sprite.setTexture(*texture);
		sprite.setPosition(position);
		sprite.scale(scale);
		
		font.loadFromFile(RESOURCES_PATH+"/"+font_name);
		desription.setFont(font);
		description.setString(message);
		description.setCharacterSize(character_size);
		description.setFillColor(color);
		description.setPosition(txt_pos);
	}

	void View::draw()
	{
		sprite.setTexture(*texture);
	}

}