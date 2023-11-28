#pragma once
#include "../Field/Field.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "View.h"
#include "ViewModule.h"
#include "ViewRobot.h"
#include <SFML/Window/Keyboard.hpp>

namespace Game
{
    struct CellHash
    {
        std::size_t operator()(const Field::Cell& key1) const
        {
            return std::hash<int>()((key1.getX() + key1.getY()) * (key1.getX() - key1.getY()) * Field::CellTypeToInt(key1.getType()));
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
    public:
        static std::string GROUND_TEXTURE;
        static std::string OBSTACLE_TEXTURE;
        static std::string ROBOT_TEXTURE;
        static std::string POI_TEXTURE;
        static std::string ENERGY_GENERATOR_TEXTURE;
        static std::string SENSOR_TEXTURE;
        static std::string MANAGE_MODULE_TEXTURE;
        static std::string GUN_TEXTURE;
        static std::string INVENTORY_ITEM_TEXTURE;
        static std::string ERROR_TEXTURE;
        static std::string FONT_NAME;
        static std::pair<int, int> SPRITE_SIZE;
        static std::pair<int, int> SCALED_SPRITE_SIZE;
        static int CHARACTER_SIZE;
        static std::pair<int, int> TOP_RIGHT_CORNER;
        static std::pair<int, int> TOP_RIGHT_CORNER_TEXT;
        static sf::Vector2f SPRITE_SCALE;
        static int LOG_INDENTATION;

        std::vector<View*> views;

        View* tmp=nullptr;
        ViewRobot* currentPlt=nullptr;
        //Robots::Platform* currentPlt = nullptr;
        std::vector<std::pair<ViewModule*, ViewModule*>> tmp_inv;
        Field::Field* field;

        void viewField(Field::Field* fld);
        View* mouseLeftClick(sf::Event event);
        View* mouseRightClick(sf::Event event);
        void moveKeyPressed(sf::Event event);

        std::pair<int, int> moveKeyToVector(sf::Keyboard::Key key)
        {
            if (key == sf::Keyboard::Up) return { -1, 0 };
            else if (key == sf::Keyboard::Down) return { 1, 0 };
            else if (key == sf::Keyboard::Left) return { 0, -1 };
            else if (key == sf::Keyboard::Right) return { 0, 1 };
            else return { 0, 0 };
        }
        //std::vector<std::pair<ViewModule*, ViewModule*>> mouseRightClick(sf::Event event);
        
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

        void generateErrorView(std::string error);
        //std::pair<sf::Sprite, sf::Text> drawCell(Field::Cell& cell, sf::Text& preSet);
        //std::pair<sf::Sprite, sf::Text> drawRobot(Robots::Platform& plt, sf::Text& preSet);
        //std::pair<sf::Sprite, sf::Text> drawModule(Robots::Module& mod, sf::Text& preSet);
        //std::vector<std::pair<sf::Sprite, sf::Sprite>> drawModuleBar(Robots::Platform& plt);

        bool isClicked(View* view, std::pair<int, int> click)
        {
            std::pair<int, int> coordinates = { view->sprite.getPosition().x, view->sprite.getPosition().y };
            std::pair<int, int> size = { view->sprite.getTexture()->getSize().x*view->sprite.getScale().x, view->sprite.getTexture()->getSize().y*view->sprite.getScale().y};
            return (click.first > coordinates.first && click.first<(coordinates.first + size.first) && click.second>coordinates.second && click.second < (coordinates.second + size.second));
        }

        /*bool inBoundaries(std::pair<int, int> click, std::pair<int, int> cell1)
        {
            return (click.second > cell1.first * SPRITE_SIZE.first && click.second<(cell1.first + 1)* SPRITE_SIZE.first&& click.first> cell1.second * SPRITE_SIZE.second && click.first < (cell1.second + 1)* SPRITE_SIZE.second);
        }

        bool clickOnSprite(std::pair<int, int> click, std::pair<int, int> sp, std::pair<int, int> spriteSize)
        {
            return (click.first > sp.first && click.first<(sp.first + spriteSize.first) && click.second>sp.second && click.second < (sp.second + spriteSize.second));
        }*/
    };
}
