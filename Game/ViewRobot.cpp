#include "ViewRobot.h"
#include "ViewModule.h"
#include "Drawer.h"
#include "../utils/CheckComponent.h"
#include "../Platforms/CommandCentre.h"
#include "../Platforms/RobotDestroyer.h"
#include "../Platforms/RobotCommander.h"
#include "../Platforms/MobilePlatform.h"
#include "../Platforms/QuantumPlatform.h"
#include "../Platforms/KamikazeRobot.h"


namespace Game
{
	void ViewRobot::draw()
	{
		description.setString(formRobotDescription(*plt));
		if(drawInventory) drawModuleBar();
	}

	std::string ViewRobot::formRobotDescription(Robots::Platform& plt)
	{
		std::string out=std::format("({}, {}) : {}\nClass: {}\nCost: {}\nEnergy Consumption: {}\n{}/{} slots are busy\n", std::to_string(plt.getX()), std::to_string(plt.getY()), plt.getName(), formTextureName(plt).substr(0, formTextureName(plt).length()-4), plt.getCost(), plt.getEnergyLevel(), plt.getRobo().size(), plt.getSlots());
		if (isComponentCastable<Robots::Platform&, Robots::Rulling&>(plt))
		{
			out += "\nsubordinates:\n";
			int i = 0;
			for (Robots::Platform* sub : dynamic_cast<Robots::CommandCentre&>(plt).getCpu().getSubOrd())
			{
				i++;
				out += std::format("{}. ({}, {}) | {}\n", std::to_string(i), std::to_string(sub->getCoordinates().first), std::to_string(sub->getCoordinates().second), sub->getName());
			}
		}
		return out;
	}

	std::string ViewRobot::formTextureName(Robots::Platform& plt)
	{
		if (isComponentCastable<Robots::Platform&, Robots::KamikazeRobot&>(plt)) return Drawer::KAMIKAZE_ROBOT_TEXTURE;
		else if (isComponentCastable<Robots::Platform&, Robots::RobotDestroyer&>(plt)) return Drawer::ROBOT_DESTROYER_TEXTURE;
		else if (isComponentCastable<Robots::Platform&, Robots::RobotCommander&>(plt)) return Drawer::ROBOT_COMMANDER_TEXTURE;
		else if (isComponentCastable<Robots::Platform&, Robots::MobilePlatform&>(plt)) return Drawer::MOBILE_PLATFORM_TEXTURE;
		else if (isComponentCastable<Robots::Platform&, Robots::QuantumPlatform&>(plt)) return Drawer::QUANTUM_PLATFORM_TEXTURE;
		else if (isComponentCastable<Robots::Platform&, Robots::CommandCentre&>(plt)) return Drawer::COMMAND_CENTRE_TEXTURE;
		else return "";
	}

	void ViewRobot::drawModuleBar()
	{
		std::pair<int, int> base_position = { plt->getCoordinates().second * Drawer::SCALED_SPRITE_SIZE.first, plt->getCoordinates().first * Drawer::SCALED_SPRITE_SIZE.second };
		for (int i=0; i<plt->getRobo().size(); i++)
		{
			
			Robots::Module* mod = plt->getRobo()[i];

			int x_other_way = 1;
			int y_other_way = 1;
			if ((field->getHeight() - plt->getCoordinates().second) < plt->getSlots())
			{
				x_other_way = -1;
				if ((field->getWidth() - plt->getCoordinates().first) < plt->getSlots()) y_other_way = -1;
			}
			if (x_other_way == -1 && y_other_way == -1) y_other_way = 1;



			ViewModule* vm = new ViewModule(mod, { base_position.first + x_other_way * (i + 1) * Drawer::SCALED_SPRITE_SIZE.first + Drawer::SCALED_SPRITE_SIZE.first / 4, base_position.second + Drawer::SCALED_SPRITE_SIZE.second / 4 }, "", {0, 0}, sf::Vector2f(0.1, 0.1));
			vm->draw();
			vm->inventoryView.sprite.setPosition(sf::Vector2f(base_position.first + x_other_way * (i + 1) * Drawer::SCALED_SPRITE_SIZE.first, y_other_way * base_position.second));
			ViewModule* vm_big = new ViewModule(mod, { Drawer::TOP_RIGHT_CORNER.first, Drawer::TOP_RIGHT_CORNER.second }, "", { Drawer::TOP_RIGHT_CORNER_TEXT.first,  Drawer::TOP_RIGHT_CORNER_TEXT.second -100}, Drawer::SPRITE_SCALE);
			vm_big->draw();
			modules.push_back({vm, vm_big});
			/*delete vm->texture;
			delete vm;
			delete vm_big->texture;
			delete vm_big;*/
		}
	}
}