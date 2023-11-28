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
        std::string out = std::format("{} \nenergyLevel {} \n {} \nis {} \ncosts {}", name, std::to_string(mod.getEnergy()), Robots::priorityToString(mod.getPriority()), mod.getState() ? "on" : "off", std::to_string(mod.getCost()));
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