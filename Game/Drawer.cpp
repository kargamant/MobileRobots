#include "Drawer.h"
std::vector<sf::Sprite> Drawer::viewField(Field::Field* fld)
{
        std::vector<sf::Sprite> sprites;
        std::pair<int, int> tlCorner = { 0, 0 };
        std::pair<int, int> brCorner = { fld->getWidth(), fld->getHeight() };
        std::pair<int, int> it = tlCorner;
        std::pair<int, int> position = { 0, 0 };
        while (it != brCorner)
        {
            sf::Texture text;
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
            text.loadFromFile("resources/" + filename);

            sf::Sprite sp;
            sp.setTexture(text);
            sp.Resize(20, 20);
            sp.setPosition(sf::Vector2f(position.first, position.second));

            sprites.push_back(sp);

            if (it.first != brCorner.first)
            {
                it.first++;
                position.first += sp.getTexture()->getSize().x * sp.getScale().x;
            }
            else
            {
                it.first = 0;
                it.second++;
                position.first = 0;
                position.second += sp.getTexture()->getSize().y * sp.getScale().y;
            }

        }
        return sprites;
}
