#include "Drawer.h"
#include <math.h>
#include <format>
#include <filesystem>
#include "../utils/CheckComponent.h"
#include "../Modules/EnergyGenerator.h"
#include "../Modules/Gun.h"
#include "../Modules/ManageModule.h"
#include "../Modules/Sensor.h"
//#include "../Modules/Module.h"

//Settings
std::string Drawer::GROUND_TEXTURE = "ground.jpg";
std::string Drawer::OBSTACLE_TEXTURE = "obstacle.png";
std::string Drawer::POI_TEXTURE = "poi.jpg";
std::string Drawer::ROBOT_TEXTURE = "robot_default.jpg";
std::string Drawer::ENERGY_GENERATOR_TEXTURE = "energy_generator.jpg";
std::string Drawer::SENSOR_TEXTURE = "sensor.png";
std::string Drawer::MANAGE_MODULE_TEXTURE = "manage_module.png";
std::string Drawer::GUN_TEXTURE = "gun.jpg";
//sf::Vector2f TOP_RIGHT_CORNER = sf::Vector2f(0, 0);
//sf::Vector2f TOP_RIGHT_CORNER_TEXT = sf::Vector2f(0, 0);

sf::Vector2f Drawer::SPRITE_SCALE = sf::Vector2f(0.2, 0.2);

int Drawer::LOG_INDENTATION = 300;


std::vector<sf::Sprite> Drawer::viewField(Field::Field* fld)
{
        std::vector<sf::Sprite> sprites;
        std::pair<int, int> tlCorner = { 0, 0 };
        std::pair<int, int> brCorner = { fld->getWidth()-1, fld->getHeight()-1 };
        std::pair<int, int> it = tlCorner;
        std::pair<int, int> position = { 0, 0 };
        field = fld;
        //std::cout << std::filesystem::current_path() << std::endl;
        while (it.first<= brCorner.first)
        {
            sf::Texture* text = new sf::Texture();
            std::string filename = coordinatesToFileName(it);
            //std::cout << filename << std::endl;
            text->loadFromFile("resources/" + filename);

            sf::Sprite sp;
            sp.setTexture(*text);
            sp.setScale(SPRITE_SCALE);

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

        TOP_RIGHT_CORNER = sf::Vector2f(sprite.first * field->getHeight() + 5, 0);
        TOP_RIGHT_CORNER_TEXT = sf::Vector2f(sprite.first * field->getHeight() + 5, sprite.second * 2);

        return sprites;
}

std::pair<std::pair<int, int>, sf::Sprite> Drawer::mouseClick(sf::Event event)
{
    std::pair<int, int> click = { event.mouseButton.x, event.mouseButton.y };
    std::pair<std::pair<int, int>, sf::Sprite> min_sp = { std::pair<int, int>(), sf::Sprite() };
    min_sp.first.first = (click.second / sprite.first);
    min_sp.first.second = (click.first / sprite.second);
    if (min_sp.first.first > field->getWidth() || min_sp.first.second > field->getHeight())
    {
        std::cout << "oops. wrong click." << std::endl;
        min_sp.first = { -1, -1 };
        return min_sp;
    }
    //std::cout << field->getCellByCoordinates(min_sp.first << std::endl;
    min_sp.second = *map[field->getCellByCoordinates(min_sp.first)];
    return min_sp;
}

/*std::pair<std::pair<int, int>, sf::Sprite> Drawer::rightMouseClick(sf::Event event)
{
    std::pair<std::pair<int, int>, sf::Sprite> pic = mouseClick(event);
    std::pair<int, int> click = pic.first;
    Robots::Platform* plt = field->checkPlatformOnField(click);
    if (plt != nullptr)
    {

    }
    
}*/

std::pair<sf::Sprite, sf::Text> Drawer::drawModule(Robots::Module& mod, sf::Text& preSet)
{
    std::string texture_name, name;
    //add extras for every module
    if (isComponentCastable<Robots::Module&, Robots::EnergyGenerator&>(mod))
    {
        name = "energy generator";
        texture_name = ENERGY_GENERATOR_TEXTURE;
    }
    else if (isComponentCastable<Robots::Module&, Robots::Sensor&>(mod))
    {
        name = "sensor";
        texture_name = SENSOR_TEXTURE;
    }
    else if (isComponentCastable<Robots::Module&, Robots::ManageModule&>(mod))
    {
        name = "manage module";
        texture_name = MANAGE_MODULE_TEXTURE;
    }
    else if (isComponentCastable<Robots::Module&, Robots::Gun&>(mod))
    {
        name = "gun";
        texture_name = GUN_TEXTURE;
    }

    sf::Sprite sprite;
    sf::Texture* texture = new sf::Texture();
    std::cout << "resources/" + texture_name << std::endl;
    texture->loadFromFile("resources/"+texture_name);
    sprite.setTexture(*texture);
    sprite.scale(SPRITE_SCALE);
    sprite.setPosition(TOP_RIGHT_CORNER);

    std::string out = std::format("{} \nenergyLevel {} \n {} \nis {} \ncosts {}", name, std::to_string(mod.getEnergy()), Robots::priorityToString(mod.getPriority()), mod.getState() ? "on" : "off", std::to_string(mod.getCost()));
    sf::Text description = preSet;
    description.setString(out);
    description.setPosition(TOP_RIGHT_CORNER_TEXT);

    return std::pair<sf::Sprite, sf::Text>(sprite, description);
}

std::pair<sf::Sprite, sf::Text> Drawer::drawCell(Field::Cell& cell, sf::Text& preSet)
{
    std::string out= std::format("({}, {}) : {}", std::to_string(cell.getX()), std::to_string(cell.getY()), Field::CellTypeToString(cell.getType()));
    
    //View view = View(coordinatesToFileName(cell.getCoordinates()), std::string font_name, int character_size, sf::Color fill_color, sf::Vector2f scale, sf::Vector2f position);
    
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
