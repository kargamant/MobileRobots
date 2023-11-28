#include "ViewRobot.h"
#include "ViewModule.h"
#include "Drawer.h"

namespace Game
{
	void ViewRobot::draw()
	{
		description.setString(formRobotDescription(*plt));
		drawModuleBar();
	}

	std::string ViewRobot::formRobotDescription(Robots::Platform& plt)
	{
		return std::format("({}, {}) : {}\nCost: {}\nEnergy Consumption: {}\n{}/{} slots are busy", std::to_string(plt.getX()), std::to_string(plt.getY()), plt.getName(), plt.getCost(), plt.getEnergyLevel(), plt.getRobo().size(), plt.getSlots());
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
			ViewModule* vm_big = new ViewModule(mod, { Drawer::TOP_RIGHT_CORNER.first, Drawer::TOP_RIGHT_CORNER.second }, "", Drawer::TOP_RIGHT_CORNER_TEXT, Drawer::SPRITE_SCALE);
			vm_big->draw();
			modules.push_back({vm, vm_big});
		}
	}
}