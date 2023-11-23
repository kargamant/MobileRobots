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
    std::vector<sf::Sprite> viewField(Field::Field* fld);
    std::pair<Field::Cell, sf::Sprite> mouseClick(sf::Event event);
};