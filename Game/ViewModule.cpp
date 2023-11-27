#include "ViewModule.h"

namespace Game
{
	void ViewModule::draw()
	{
        std::pair<std::string, std::string> naming = moduleToName(mod);
        texture_name = naming.second;
        name = naming.first;

        texture->loadFromFile(RESOURCES_PATH+"/" + texture_name);
        sprite.setTexture(*texture);

        std::string out = std::format("{} \nenergyLevel {} \n {} \nis {} \ncosts {}", name, std::to_string(mod->getEnergy()), Robots::priorityToString(mod->getPriority()), mod->getState() ? "on" : "off", std::to_string(mod->getCost()));
        description.setString(out);
	}

    std::pair<std::string, std::string> ViewModule::moduleToName(Robots::Module& mod)
    {
        std::string name, texture_name;
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

        return std::pair<std::string, std::string>(name, texture_name);
    }
}