#include "Drawer.h"
#include <math.h>
#include <format>

std::vector<sf::Sprite> Drawer::viewField(Field::Field* fld)
{
        std::vector<sf::Sprite> sprites;
        std::pair<int, int> tlCorner = { 0, 0 };
        std::pair<int, int> brCorner = { fld->getWidth()-1, fld->getHeight()-1 };
        std::pair<int, int> it = tlCorner;
        std::pair<int, int> position = { 0, 0 };
        field = fld;
        while (it.first<= brCorner.first)
        {
            sf::Texture* text = new sf::Texture();
            std::string filename = coordinatesToFileName(it);
            //std::cout << filename << std::endl;
            text->loadFromFile("resources/" + filename);

            sf::Sprite sp;
            sp.setTexture(*text);
            sp.setScale(sf::Vector2f(0.2, 0.2));

            sprite.first = sp.getTexture()->getSize().x * sp.getScale().x;
            sprite.second = sp.getTexture()->getSize().y * sp.getScale().y;
            //std::cout << sprite.first << " " << sprite.second << std::endl;

            sp.setPosition(sf::Vector2f(position.first, position.second));

            sprites.push_back(sp);
            //map.push_back(std::pair<Field::Cell&, sf::Sprite>(fld->getCellByCoordinates(it), sp));
            map.insert({ fld->getCellByCoordinates(it), &sp });

            if (it.second != brCorner.second)
            {
                it.second++;
                position.first += sp.getTexture()->getSize().x * sp.getScale().x;
            }
            else
            {
                it.first++;
                it.second=0;
                position.first = 0;
                position.second += sp.getTexture()->getSize().y * sp.getScale().y;
            }

        }
        return sprites;
}

std::pair<std::pair<int, int>, sf::Sprite> Drawer::mouseClick(sf::Event event)
{
    std::pair<int, int> click = { event.mouseButton.x, event.mouseButton.y };
    std::pair<std::pair<int, int>, sf::Sprite> min_sp = { std::pair<int, int>(), sf::Sprite() };
    min_sp.first.first = (click.second / sprite.first);
    min_sp.first.second = (click.first / sprite.second);
    min_sp.second = *map[field->getCellByCoordinates(min_sp.first)];
    return min_sp;
}

std::pair<sf::Sprite, sf::Text> Drawer::drawCell(Field::Cell& cell, sf::Text& preSet)
{
    std::string out= std::format("({}, {}) : {}", std::to_string(cell.getX()), std::to_string(cell.getY()), Field::CellTypeToString(cell.getType()));
    sf::Text description = preSet;
    description.setString(out);
    description.setPosition(sf::Vector2f(sprite.first * field->getHeight() + 5, sprite.second * 2));

    std::cout << out << std::endl;
    sf::Texture* port_text = new sf::Texture();
    sf::Sprite portrait = sf::Sprite();
    port_text->loadFromFile("resources/" + coordinatesToFileName(cell.getCoordinates()));
    portrait.setTexture(*port_text);
    portrait.scale(sf::Vector2f(0.4, 0.4));
    portrait.setPosition(sf::Vector2f(sprite.first * field->getHeight() + 5, 0));

    return std::pair<sf::Sprite, sf::Text>(portrait, description);
}

std::pair<sf::Sprite, sf::Text> Drawer::drawRobot(Robots::Platform& plt, sf::Text& preSet)
{
    std::string out= std::format("({}, {}) : {}", std::to_string(plt.getX()), std::to_string(plt.getY()), plt.getName());
    
    sf::Text description = preSet;
    description.setString(out);
    description.setPosition(sf::Vector2f(sprite.first * field->getHeight() + 5, sprite.second * 2));

    std::cout << out << std::endl;
    sf::Texture* port_text = new sf::Texture();
    sf::Sprite portrait = sf::Sprite();
    port_text->loadFromFile("resources/" + coordinatesToFileName(plt.getCoordinates()));
    portrait.setTexture(*port_text);
    portrait.scale(sf::Vector2f(0.4, 0.4));
    portrait.setPosition(sf::Vector2f(sprite.first * field->getHeight() + 5, 0));

    return std::pair<sf::Sprite, sf::Text>(portrait, description);
}
