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
    static int LOG_INDENTATION;
public:
    std::unordered_map<Field::Cell, sf::Sprite*, CellHash, CellEqual> map;
    Field::Field* field;
    std::pair<int, int> sprite;

    std::vector<sf::Sprite> viewField(Field::Field* fld);
    std::pair<std::pair<int, int>, sf::Sprite> mouseClick(sf::Event event);
    std::string coordinatesToFileName(std::pair<int, int> coordinates)
    {
        std::string filename;
        switch (field->getCellByCoordinates(coordinates).getType())
        {
        case Field::CellType::ground:
            filename = GROUND_TEXTURE;
            break;
        case Field::CellType::obstacle:
            filename = OBSTACLE_TEXTURE;
            break;
        case Field::CellType::pointOfInterest:
            filename = POI_TEXTURE;
            break;
        }
        if (field->checkPlatformOnField(coordinates) != nullptr) filename = ROBOT_TEXTURE;
        return filename;
    }

    std::pair<sf::Sprite, sf::Text> drawCell(Field::Cell& cell, sf::Text& preSet);
    std::pair<sf::Sprite, sf::Text> drawRobot(Robots::Platform& plt, sf::Text& preSet);

    bool inBoundaries(std::pair<int, int> click, std::pair<int, int> cell1)
    {
        return (click.second > cell1.first * sprite.first && click.second<(cell1.first + 1)* sprite.first&& click.first> cell1.second * sprite.second && click.first < (cell1.second + 1)* sprite.second);
    }

    int getLogIndentation() { return LOG_INDENTATION; }
};

/*
class View
{
//parameters
private:
    std::string TEXTURE_NAME;
    std::string FONT_NAME;
    int CHARACTER_SIZE;
    sf::Color FILL_COLOR;
    sf::Vector2f SCALE;
    sf::Vector2f POSITION;
public:
    sf::Sprite portrait;
    sf::Text description;
    View(std::string texture_name, std::string font_name, int character_size, sf::Color fill_color, sf::Vector2f scale, sf::Vector2f position) :TEXTURE_NAME(texture_name), FONT_NAME(font_name), CHARACTER_SIZE(character_size), FILL_COLOR(fill_color), SCALE(scale), POSITION(position)
    {
        sf::Texture* texture = new sf::Texture();
        texture->loadFromFile("resources/"+TEXTURE_NAME);
        portrait.setTexture(*texture);
        portrait.scale(SCALE);
        portrait.setPosition(POSITION);

        sf::Font font;
        font.loadFromFile("resources/"+font_name);
        description.setFont(font);
        description.setCharacterSize(character_size);
        description.setFillColor(FILL_COLOR);
    }

};*/