#include <SFML/Graphics.hpp>
#include "../Field/Field.h"
#include "Drawer.h"
#include "../Platforms/RobotCommander.h"

//Settings
int Field::Field::MAX_RANDOM_SIZE = 10;
std::string Drawer::GROUND_TEXTURE = "ground.jpg";
std::string Drawer::OBSTACLE_TEXTURE = "obstacle.png";
std::string Drawer::POI_TEXTURE = "poi.jpg";
std::string Drawer::ROBOT_TEXTURE = "robot_default.jpg";
int Drawer::LOG_INDENTATION = 300;

int main()
{
    
    
    Field::Field* fld = new Field::Field();

    //test platform placement
    Robots::RobotCommander* rc = new Robots::RobotCommander();
    rc->setCoordinates(2, 3);
    fld->placePlatform(rc);

    Drawer dr;
    std::vector<sf::Sprite> sprites = dr.viewField(fld);
    sf::RenderWindow window(sf::VideoMode(dr.sprite.first*fld->getHeight()+dr.getLogIndentation(), dr.sprite.second * fld->getWidth()), "MobileRobots");

    //text initializer
    sf::Font pixel_font;
    pixel_font.loadFromFile("resources/munro-small.ttf");
    sf::Text consoleOut;
    sf::Text description;
    consoleOut.setFont(pixel_font);
    consoleOut.setCharacterSize(20);
    consoleOut.setFillColor(sf::Color::White);

    //pic initializer
    sf::Sprite portrait;
    portrait.scale(sf::Vector2f(0.4, 0.4));
    sf::Texture* portrait_text = new sf::Texture();
    
    bool isGameStart = true;
    while (window.isOpen())
    {
        window.clear();
        bool isSceneChanged = false;
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::pair<std::pair<int, int>, sf::Sprite> closest_cell = dr.mouseClick(event);
                    if (closest_cell.first.first == -1 && closest_cell.first.second== -1)
                    {
                        continue;
                    }
                    //std::cout << closest_cell.first.first << " " << closest_cell.first.second << std::endl;
                    std::pair<int, int> clickObj = closest_cell.first;
                    Robots::Platform* plt = fld->checkPlatformOnField(clickObj);
                    std::pair<sf::Sprite, sf::Text> picture;
                    if (plt != nullptr)
                    {
                        picture = dr.drawRobot(*plt, consoleOut);
                    }
                    else
                    {
                        picture = dr.drawCell(fld->getCellByCoordinates(clickObj), consoleOut);
                    }
                    portrait = picture.first;
                    description = picture.second;
                    isSceneChanged = true;
                }
            }
        }

        
        //window.draw(sprites[0]);
        
        if (isSceneChanged || isGameStart)
        {
            for (sf::Sprite& robo : sprites)
            {
                window.draw(robo);
            }
            window.draw(portrait);
            window.draw(description);
        }
        window.display();
    }

    for (sf::Sprite& robo : sprites)
    {
        delete robo.getTexture();
    }
    delete fld;
    delete portrait_text;
    return 0;
}



