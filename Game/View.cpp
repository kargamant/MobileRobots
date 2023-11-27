#include "Drawer.h"

namespace Game
{
	std::string View::FONT_NAME= "munro-small.ttf";
	std::string View::ROBOT_TEXTURE = "robot_default.jpg";
	std::string View::RESOURCES_PATH = "resources/";
	int View::CHARACTER_SIZE=20;
	sf::Vector2f View::SPRITE_SCALE= sf::Vector2f(0.2, 0.2);
	sf::Color View::TEXT_COLOR=sf::Color::White;

	View::View(std::string texture_name, sf::Vector2f position, std::string message, sf::Vector2f txt_pos, sf::Vector2f scale, std::string font_name, int character_size, sf::Color color)
	{
		texture = new sf::Texture();
		texture->loadFromFile(RESOURCES_PATH + "/" + texture_name);
		sprite.setTexture(*texture);
		sprite.setPosition(position);
		sprite.scale(scale);
		
		font.loadFromFile(RESOURCES_PATH+"/"+font_name);
		description.setFont(font);
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