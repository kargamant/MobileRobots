#pragma once
#include "../Field/Field.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>


struct CellHash
{
    std::size_t operator()(const Field::Cell& key1) const
    {
        return std::hash<int>()((key1.getX() + key1.getY()) * (key1.getX() - key1.getY())*Field::CellTypeToInt(key1.getType()));
    }
};

struct CellEqual
{
    bool operator()(const Field::Cell& key1, const Field::Cell& key2) const
    {
        return key1.getCoordinates() == key2.getCoordinates() && key1.getType() == key2.getType();
    }
};

class Drawer
{
private:
    static std::string GROUND_TEXTURE;
    static std::string OBSTACLE_TEXTURE;
    static std::string ROBOT_TEXTURE;
    static std::string POI_TEXTURE;
public:
    std::unordered_map<Field::Cell, sf::Sprite*, CellHash, CellEqual> map;
    //std::vector<std::pair<Field::Cell, sf::Sprite>> map;
    Field::Field* field;
    std::pair<int, int> sprite;

    std::vector<sf::Sprite> viewField(Field::Field* fld);
    std::pair<Field::Cell, sf::Sprite> mouseClick(sf::Event event);

    bool inBoundaries(std::pair<int, int> click, std::pair<int, int> cell1)
    {
        return (click.second > cell1.first * sprite.first && click.second<(cell1.first + 1)* sprite.first&& click.first> cell1.second * sprite.second && click.first < (cell1.second + 1)* sprite.second);
    }

    /*sf::Sprite& getSpriteByCoordinates(std::pair<int, int> coordinates)
    {
        for (std::pair<Field::Cell, sf::Sprite>& sp : map)
        {
            if (sp.first.getCoordinates() == coordinates) return sp.second;
        }
        return map[0].second;
    }*/
};