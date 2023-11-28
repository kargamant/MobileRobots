#include "View.h"
#include "../Field/Cell.h"
#pragma once

namespace Game
{
	class ViewCell :public View
	{
    private:
        static std::string GROUND_TEXTURE;
        static std::string OBSTACLE_TEXTURE;
        static std::string POI_TEXTURE;
        std::string cellToFileName(Field::Cell& cell);
        std::string formCellDescription(Field::Cell& cell);
	public:
		Field::Cell* cell;
        ViewCell(Field::Cell* cell, std::pair<int, int> position, std::string message, std::pair<int, int> txt_pos, sf::Vector2f scale = SPRITE_SCALE, std::string font_name = FONT_NAME, int character_size = CHARACTER_SIZE, sf::Color color = TEXT_COLOR) : cell(cell), View(cellToFileName(*cell), position, message, txt_pos, scale, font_name, character_size, color) {}
	    
        void draw() override;
    };

    sf::Vector2f fieldCoordinatesToGlobal(std::pair<int, int> coordinates);
    std::pair<int, int> globalCoordinatesToField(sf::Vector2f coordinates);
}