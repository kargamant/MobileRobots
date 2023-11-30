#include "ViewModule.h"
#include "Drawer.h"
#include "../Modules/EnergyGenerator.h"
#include "../Modules/Gun.h"
#include "../Modules/ManageModule.h"
#include "../Modules/Sensor.h"
#include "../utils/CheckComponent.h"

namespace Game
{
    std::string ViewModule::INVENTORY_ITEM_TEXTURE = "inventory.jpg";

	void ViewModule::draw()
	{
        
        //texture->loadFromFile(RESOURCES_PATH+"/" + texture_name);
        sprite.setTexture(*texture);

        std::string out = formModuleDescription(*mod);
        description.setString(out);
	}

    std::string ViewModule::formModuleDescription(Robots::Module& mod)
    {
        std::pair<std::string, std::string> naming = moduleToName(mod);
        std::string texture_name = naming.second;
        std::string name = naming.first;
        std::string out = std::format("{} \nenergyLevel {} \n {} \nis {} \ncosts {}\n", name, std::to_string(mod.getEnergy()), Robots::priorityToString(mod.getPriority()), mod.getState() ? "on" : "off", std::to_string(mod.getCost()));
        if (mod.isRulling)
        {
            out += std::format("radius: {}\n", dynamic_cast<Robots::ManageModule&>(mod).getRad());
            out += std::format("sub {}/{}\n", dynamic_cast<Robots::ManageModule&>(mod).getSubOrd().size(), dynamic_cast<Robots::ManageModule&>(mod).getSub());
            out += "\nsubordinates:\n";
            int i = 0;
            for (Robots::Platform* sub : dynamic_cast<Robots::ManageModule&>(mod).getSubOrd())
            {
                i++;
                out += std::format("{}. ({}, {}) | {}\n", std::to_string(i), std::to_string(sub->getCoordinates().first), std::to_string(sub->getCoordinates().second), sub->getName());
            }
        }
        else if (mod.isSensor)
        {
            out += "radius: " + std::to_string(dynamic_cast<Robots::Sensor&>(mod).getRad()) + "\n";
            out += std::format("direction: ({}, {})\n", std::to_string(dynamic_cast<Robots::Sensor&>(mod).getDirection().first), std::to_string(dynamic_cast<Robots::Sensor&>(mod).getDirection().second));
            out += std::format("angle: {}\n", Robots::angleToString(dynamic_cast<Robots::Sensor&>(mod).getAngle()));
        }
        else if (mod.isEnergyGenerator)
        {
            out += "energySupply: " + std::to_string(dynamic_cast<Robots::EnergyGenerator&>(mod).getEnergySup()) + "\n";
            out += "Usage: " + std::to_string(dynamic_cast<Robots::EnergyGenerator&>(mod).getCurrentLoad()) + "\n";
            out += "\nConnected modules:\n";

            int i = 0;
            for (Robots::Module* m : dynamic_cast<Robots::EnergyGenerator&>(mod).getConnected())
            {
                ++i;
                out += std::format("{}. {} is {}\n", std::to_string(i), moduleToName(*m).first, m->getState() ? "on" : "off");
            }
        }
        return out;
    }

    std::pair<std::string, std::string> ViewModule::moduleToName(Robots::Module& mod)
    {
        std::string name, texture_name;
        if (isComponentCastable<Robots::Module&, Robots::EnergyGenerator&>(mod))
        {
            name = "energy generator";
            texture_name = Drawer::ENERGY_GENERATOR_TEXTURE;
        }
        else if (isComponentCastable<Robots::Module&, Robots::Sensor&>(mod))
        {
            name = "sensor";
            texture_name = Drawer::SENSOR_TEXTURE;
        }
        else if (isComponentCastable<Robots::Module&, Robots::ManageModule&>(mod))
        {
            name = "manage module";
            texture_name = Drawer::MANAGE_MODULE_TEXTURE;
        }
        else if (isComponentCastable<Robots::Module&, Robots::Gun&>(mod))
        {
            name = "gun";
            texture_name = Drawer::GUN_TEXTURE;
        }

        return std::pair<std::string, std::string>(name, texture_name);
    }
}