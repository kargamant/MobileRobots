#include "Drawer.h"
#include <math.h>

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
            std::string filename;
            switch (fld->getCellByCoordinates(it).getType())
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
            if (fld->checkPlatformOnField(it) != nullptr) filename = ROBOT_TEXTURE;
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

std::pair<Field::Cell, sf::Sprite> Drawer::mouseClick(sf::Event event)
{
    std::pair<int, int> click = { event.mouseButton.x, event.mouseButton.y };
    std::pair<Field::Cell, sf::Sprite> min_sp = {Field::Cell(), sf::Sprite()};
    for (int i = 0; i < field->getWidth(); i++)
    {
        for (int j = 0; j < field->getHeight(); j++)
        {
            //std::cout << i << " " << j << std::endl;
            if (inBoundaries(click, {i , j}))
            {
                min_sp.first = field->getCellByCoordinates({i, j});
                min_sp.second = *map[min_sp.first];
                return min_sp;
            }
        }
    }
    /*int min_distance = 1000000;
    for (std::pair<Field::Cell, sf::Sprite>& sp : map)
    {
        int distance = std::sqrt((click.first-sp.second.getPosition().x)* (click.first - sp.second.getPosition().x)+ (click.second - sp.second.getPosition().y)* (click.second - sp.second.getPosition().y));
        if (distance < min_distance)
        {
            min_distance = distance;
            min_sp = sp;
        }
    }*/
    return min_sp;
}
