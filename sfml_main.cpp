#include <SFML/Graphics.hpp>
#include "Field/Field.h"
#include "Game/Drawer.h"
#include "Platforms/RobotCommander.h"
#include "Platforms/RobotDestroyer.h"
#include "Platforms/CommandCentre.h"
#include "Modules/Sensor.h"
#include "Modules/EnergyGenerator.h"
#include "Platforms/QuantumPlatform.h"
#include "utils/CheckComponent.h"
#include "Platforms/MobilePlatform.h"

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
    rc->setCoordinates(0, 0);
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
    Robots::Platform* currentPlt = nullptr;
    while (window.isOpen())
    {
        window.clear();
        bool isSceneChanged = false;
        bool isFieldChanged = false;
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
                            currentPlt = plt;
                            std::cout << currentPlt->getName() << std::endl;
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
                    Robots::Module* mod = dr.detectClickOnBar(event, *currentPlt, module_bar);
                    if (mod != nullptr)
                    {
                        std::pair<sf::Sprite, sf::Text> module_picture = dr.drawModule(*mod, consoleOut);
                        portrait = module_picture.first;
                        description = module_picture.second;
                    }
                }
                isSceneChanged = true;
            }
            else if (event.type==sf::Event::KeyPressed)
            {
                std::pair<int, int> vector;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) vector = { 0, -1 };
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) vector = { 0, 1 };
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) vector = { -1, 0 };
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) vector = { 1, 0 };
                if (currentPlt != nullptr)
                {
                    bool isErr = false;
                    //if (!isComponentCastable<Robots::MobilePlatform*, Robots::Platform*>(plt)) description.setString("");
                    try
                    {
                        module_bar = std::vector<std::pair<sf::Sprite, sf::Sprite>>();
                        std::cout << currentPlt->getCoordinates().first <<" "<<currentPlt->getCoordinates().second << std::endl;
                        dynamic_cast<Robots::Moving&>(*currentPlt).move(fld, vector);
                    }
                    catch (std::invalid_argument error)
                    {
                        isErr = true;
                        description.setString(error.what());
                    }
                    catch (std::bad_cast error2)
                    {
                        isErr = true;
                        description.setString("Error. Platform is not movable.");
                    }
                    isFieldChanged = true;
                    if (!isErr)
                    {
                        description = dr.drawRobot(*currentPlt, consoleOut).second;
                    }
                }   
            }
        }
        if (isFieldChanged)
        {
            for (sf::Sprite sp : sprites)
            {
                delete sp.getTexture();
            }
            sprites = dr.viewField(fld);
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



