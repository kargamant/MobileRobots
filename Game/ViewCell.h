#include "View.h"
#include "../Field/Cell.h"


namespace Game
{
	class ViewCell :public View
	{
    private:
        static std::string GROUND_TEXTURE;
        static std::string OBSTACLE_TEXTURE;
        static std::string POI_TEXTURE;
        std::string cellToFileName(Field::Cell& cell);
	public:
		Field::Cell* cell;
        ViewCell(Field::Cell* cell, std::string texture_name, sf::Vector2f scale, sf::Vector2f position, std::string message, std::string font_name, int character_size, sf::Color color, sf::Vector2f txt_pos) : cell(cell), View(texture_name, scale, position, message, font_name, character_size, color, txt_pos) {}
	    
        void draw() override;
    };

}