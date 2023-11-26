#include <SFML/Graphics.hpp>
#include "Field/Field.h"
#include "Game/Drawer.h"
#include "Platforms/RobotCommander.h"
#include "Platforms/RobotDestroyer.h"
#include "Platforms/CommandCentre.h"
#include "Modules/Sensor.h"
#include "Modules/EnergyGenerator.h"
#include "Platforms/QuantumPlatform.h"

int main()
{
    
    
    Field::Field* fld = new Field::Field();

    //test platform placement
    Robots::RobotCommander* rc = new Robots::RobotCommander();
    Robots::RobotDestroyer* rd = new Robots::RobotDestroyer();
    Robots::CommandCentre* cc = new Robots::CommandCentre(2, 2, 1, 3, 2000);
    Robots::QuantumPlatform* qc = new Robots::QuantumPlatform();

    qc->setSlots(5);
    qc->setCoordinates(fld->getWidth() - 1, 0);
    cc->setCoordinates(fld->getWidth()-1, fld->getHeight() - 1);
    Robots::EnergyGenerator gen = Robots::EnergyGenerator();
    cc->placeModule(gen);
    rd->setCoordinates(0, 0);
    Robots::Sensor sens = Robots::Sensor(1, { 2, 3 }, Robots::ViewAngles::tau, 2, true, Robots::Priority::high, 5000);
    qc->placeModule(sens);
    qc->placeModule(sens);
    qc->placeModule(sens);
    cc->placeModule(sens);
    rd->placeModule(sens);
    rc->setCoordinates(2, 3);
    fld->placePlatform(rc);
    fld->placePlatform(rd);
    fld->placePlatform(cc);
    fld->placePlatform(qc);

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
    std::vector<std::pair<sf::Sprite, sf::Sprite>> module_bar;
    Robots::Platform currentPlt;
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
                    if (closest_cell.first.first != -1 && closest_cell.first.second!= -1)
                    {
                        std::pair<int, int> clickObj = closest_cell.first;
                        Robots::Platform* plt = fld->checkPlatformOnField(clickObj);
                        std::pair<sf::Sprite, sf::Text> picture;
                        if (plt != nullptr)
                        {
                            picture = dr.drawRobot(*plt, consoleOut);
                            if(plt->getRobo().size()!=0)module_bar = dr.drawModuleBar(*plt);
                            currentPlt = *plt;
                        }
                        else
                        {
                            picture = dr.drawCell(fld->getCellByCoordinates(clickObj), consoleOut);
                            module_bar = std::vector<std::pair<sf::Sprite, sf::Sprite>>();
                        }
                        portrait = picture.first;
                        description = picture.second;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    Robots::Module* mod = dr.detectClickOnBar(event, currentPlt, module_bar);
                    if (mod != nullptr)
                    {
                        std::pair<sf::Sprite, sf::Text> module_picture = dr.drawModule(*mod, consoleOut);
                        portrait = module_picture.first;
                        description = module_picture.second;
                    }
                }
                isSceneChanged = true;
            }
        }
        
        if (isSceneChanged || isGameStart)
        {
            for (sf::Sprite& robo : sprites)
            {
                window.draw(robo);
            }
            window.draw(portrait);
            window.draw(description);
            for (std::pair<sf::Sprite, sf::Sprite> pair : module_bar)
            {
                window.draw(pair.first);
                window.draw(pair.second);
            }
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



