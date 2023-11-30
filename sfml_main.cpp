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
#include "Game/ViewRobot.h"
#include "Game/ViewCell.h"
#include "Platforms/KamikazeRobot.h"
//#include "Modules/Gun.h"


int main()
{
    
    Field::Field::GROUND_MODE_ON = false;
    Field::Field* fld = new Field::Field();
    Robots::RobotCommander* rc = new Robots::RobotCommander();
    rc->setSlots(5);

    std::srand(time(NULL));

    Robots::Sensor sens = Robots::Sensor();
    Robots::EnergyGenerator eg= Robots::EnergyGenerator();
    Robots::RobotDestroyer rd = Robots::RobotDestroyer();
    Robots::KamikazeRobot kr = Robots::KamikazeRobot();
    Robots::MobilePlatform mp = Robots::MobilePlatform();
    Robots::QuantumPlatform qp = Robots::QuantumPlatform();

    eg.connect(sens);
    qp.setCoordinates(4, 3);
    //mp.placeModule(sens);
    rc->getCpu().setRadius(2);
    mp.setCoordinates(1, 3);
    fld->placePlatform(&mp);
    kr.setCoordinates(2, 2);
    kr.setMaxRadius(3);
    fld->placePlatform(&kr);
    Robots::Gun gun = Robots::Gun();
    rd.getGun().setMaxRadius(3);
    rd.setCoordinates(1, 1);
    fld->placePlatform(&rd);
    rc->placeModule(sens);
    rc->placeModule(gun);
    rc->placeModule(eg);
    rc->setCoordinates(0, 0);
    fld->placePlatform(rc);
    fld->placePlatform(&qp);
    //rc->getCpu().subdue(rd);
    //std::cout << "subordinate: " << rc->getCpu().getSubOrd()[0].getName() << std::endl;

    Game::Drawer dr;
    dr.viewField(fld);
    sf::RenderWindow window(sf::VideoMode(Game::Drawer::SCALED_SPRITE_SIZE.first * fld->getHeight() + Game::Drawer::LOG_INDENTATION, Game::Drawer::SCALED_SPRITE_SIZE.second * fld->getWidth()), "MobileRobots");
    //dr.window = &window;
    std::pair<bool, std::string> isPicking = { false, "" };
    bool moduleConnection = false;
    while (window.isOpen())
    {
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
                    //std::cout << dr.currentPlt->plt->getName() << std::endl;
                    Game::View* view=dr.mouseLeftClick(event);
                    //std::cout << std::string(view->description.getString()) << std::endl;
                    if (isPicking.first)
                    {
                        switch ((char)isPicking.second[0])
                        {
                        case 'D':
                            dr.destroyKeyPressed(view);
                            break;
                        case 'S':
                            dr.subdueKeyPressed(view);
                            //std::cout << "master: "<<(dynamic_cast<Game::ViewRobot*>(view)->master == nullptr) << std::endl;
                            break;
                        case 'R':
                            dr.releaseKeyPressed(view);
                            break;
                        case 'G':
                            dr.reportKeyPressed(view);
                            break;
                        }
                        
                        isFieldChanged = true;
                        isPicking.first = false;
                    }
                    else
                    {
                        if (view != nullptr)
                        {
                            if (view->isRobot)
                            {
                                //std::cout << "master: " << (dynamic_cast<Game::ViewRobot*>(view)->master == nullptr) << std::endl;
                                dr.currentPlt = dynamic_cast<Game::ViewRobot*>(view);
                            }
                        }
                        
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    Game::View* choice=dr.mouseRightClick(event);
                    if (isPicking.first)
                    {
                        switch ((char)isPicking.second[0])
                        {
                        case 'C':
                            dr.connectKeyPressed(choice);
                            break;
                        }
                        isPicking.first = false;
                        moduleConnection = false;
                    }
                    else
                    {
                        dr.currentModule = dynamic_cast<Game::ViewModule*>(choice);
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                sf::Keyboard::Key scanCode = event.key.code;
                if (dr.tmp!=nullptr && dr.currentPlt!=nullptr && dr.moveKeyToVector(scanCode) != std::pair<int, int>(0, 0))
                {
                    //std::cout << "master move: " << (dr.currentPlt->master == nullptr) << std::endl;
                    dr.moveKeyPressed(event);
                    //dr.tmp = nullptr;
                    dr.currentPlt = nullptr;
                    isFieldChanged = true;
                }
                if (scanCode == sf::Keyboard::Key::D)
                {
                    if (dr.tmp != nullptr)
                    {
                        if (dr.tmp->isModule)
                        {
                            dr.moduleDeleteKeyPressed();
                        }
                        else dr.processKey<Robots::Destroying, Game::ViewRobot, Robots::Platform>(dr.currentPlt, dr.currentPlt->plt, "destroying", "destroy", "cell", "D", isPicking);
                    }
                }
                if (scanCode == sf::Keyboard::Key::S)
                {
                    dr.processKey<Robots::Rulling, Game::ViewRobot, Robots::Platform>(dr.currentPlt, dr.currentPlt->plt, "rulling", "subdue", "robot", "S", isPicking);
                }
                if (scanCode == sf::Keyboard::Key::R)
                {
                    dr.processKey<Robots::Rulling, Game::ViewRobot, Robots::Platform>(dr.currentPlt, dr.currentPlt->plt, "rulling", "release", "robot", "R", isPicking);
                }
                if (scanCode == sf::Keyboard::Key::G)
                {
                    dr.processKey<Robots::Rulling, Game::ViewRobot, Robots::Platform>(dr.currentPlt, dr.currentPlt->plt, "rulling", "report", "robot", "G", isPicking);
                }
                if (scanCode == sf::Keyboard::Key::M)
                {
                    dr.modulePlacementKeyPressed();
                }
                if (scanCode == sf::Keyboard::Key::O)
                {
                    dr.moduleOnKeyPressed();
                }
                if (scanCode == sf::Keyboard::Key::C)
                {
                    moduleConnection = true;
                    dr.processKey<Robots::EnergyGenerator, Game::ViewModule, Robots::Module>(dr.currentModule, dr.currentModule->mod, "", "connect", "module", "C", isPicking);
                }
            }
        }
        window.clear();
        if(isFieldChanged) dr.viewField(fld);
        for (Game::View* view : dr.views)
        {
            window.draw(view->sprite);
        }
        
        if (dr.tmp != nullptr)
        {
            window.draw(dr.tmp->sprite);
            window.draw(dr.tmp->description);
            
            if (dr.currentPlt!=nullptr && (dynamic_cast<Game::ViewRobot*>(dr.tmp) == dr.currentPlt || dr.tmp->isModule || moduleConnection))
            {
                for (std::pair<Game::ViewModule*, Game::ViewModule*>& pair : dr.currentPlt->modules)
                {
                    window.draw(pair.first->inventoryView.sprite);
                    window.draw(pair.first->sprite);
                }
            }
            
        }
        window.display();
        //if (isPicking) goto destroying;
    }
    /*
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
    sf::RenderWindow window;
    window.init(sf::VideoMode(dr.sprite.first * fld->getHeight() + dr.getLogIndentation(), dr.sprite.second * fld->getWidth()), "MobileRobots");

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
    
    //bool isGameStart = true;
    //std::vector<std::pair<sf::Sprite, sf::Sprite>> module_bar;
    //Robots::Platform* currentPlt = nullptr;
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
                    std::pair<sf::Sprite, sf::Text> info = dr.getInfoFromClick(closest_cell, consoleOut);
                    portrait = info.first;
                    description = info.second;
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
    */
    return 0;
}



