#include <SFML/Graphics.hpp>
#include "../Field/Field.h"
#include "Drawer.h"

int Field::Field::MAX_RANDOM_SIZE = 10;
std::string Drawer::GROUND_TEXTURE = "ground.jpg";
std::string Drawer::OBSTACLE_TEXTURE = "obstacle.png";
std::string Drawer::POI_TEXTURE = "poi.jpg";
std::string Drawer::ROBOT_TEXTURE = "robot_default.jpg";

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "MobileRobots");
    
    Field::Field* fld();
    std::vector<sf::Sprite> sprites = Drawer::viewField(fld);
    /*sf::Texture robo_text;
    robo_text.loadFromFile("resources/robot_default.jpg");


    std::vector<sf::Sprite> sprites(10);
    std::pair<int, int> coordinates = { 0, 0 };

    for(sf::Sprite& sp:sprites)
    {
        sp.setTexture(robo_text);
        sp.scale(sf::Vector2f(0.2, 0.2));
        sp.setPosition(sf::Vector2f(coordinates.first, coordinates.second));
        coordinates.first += sp.getTexture()->getSize().x * sp.getScale().x;
        //coordinates.second += sp.getTexture()->getSize().y * sp.getScale().y;
    }*/
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (sf::Sprite& robo : sprites)
        {
            window.draw(robo);
        }
        window.display();
    }

    return 0;
}



