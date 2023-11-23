#pragma once
#include "../Field/Field.h"
#include <SFML/Graphics.hpp>

class Drawer
{
private:
    static std::string GROUND_TEXTURE;
    static std::string OBSTACLE_TEXTURE;
    static std::string ROBOT_TEXTURE;
    static std::string POI_TEXTURE;
public:
    std::vector<std::pair<Field::Cell, sf::Sprite>> map;
    Field::Field* field;
    std::pair<double, double> sprite;

    std::vector<sf::Sprite> viewField(Field::Field* fld);
    std::pair<Field::Cell, sf::Sprite> mouseClick(sf::Event event);

    bool inBoundaries(std::pair<int, int> click, std::pair<int, int> cell1)
    {
        return (click.first > cell1.first * sprite.first && click.first<(cell1.first + 1)* sprite.first&& click.second> cell1.second * sprite.second && click.second < (cell1.second + 1)* sprite.second);
    }

    sf::Sprite& getSpriteByCoordinates(std::pair<int, int> coordinates)
    {
        for (std::pair<Field::Cell, sf::Sprite>& sp : map)
        {
            if (sp.first.getCoordinates() == coordinates) return sp.second;
        }
        return map[0].second;
    }
};