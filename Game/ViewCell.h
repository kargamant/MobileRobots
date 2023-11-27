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
        ViewCell(Field::Cell* cell, sf::Vector2f position, std::string message, sf::Vector2f txt_pos, sf::Vector2f scale = Drawer::SPRITE_SCALE, std::string font_name = Drawer::FONT_NAME, int character_size = Drawer::CHARACTER_SIZE, sf::Color color = sf::Color::White) : cell(cell), View(cellToFileName(*cell), position, message, txt_pos, scale, font_name, character_size, color) {}
	    
        void draw() override;
    };

    sf::Vector2f fieldCoordinatesToGlobal(std::pair<int, int> coordinates);
    std::pair<int, int> globalCoordinatesToField(sf::Vector2f coordinates);
}