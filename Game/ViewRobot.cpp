#include "ViewRobot.h"
#include "ViewModule.h"

namespace Game
{
	void ViewRobot::draw()
	{
		description.setString(std::format("({}, {}) : {}", std::to_string(plt->getX()), std::to_string(plt->getY()), plt->getName()));
		drawModuleBar();
	}

	void ViewRobot::drawModuleBar()
	{
		std::pair<int, int> base_position = { plt->getCoordinates().second * Drawer::SPRITE_SIZE.first, plt->getCoordinates().first * Drawer::SPRITE_SIZE.second };
		for (int i=0; i<plt->getRobo().size(); i++)
		{
			Robots::Module* mod = plt[i];

			int x_other_way = 1;
			int y_other_way = 1;
			if ((field->getHeight() - plt->getCoordinates().second) < plt.getSlots())
			{
				x_other_way = -1;
				if ((field->getWidth() - plt.getCoordinates().first) < plt.getSlots()) y_other_way = -1;
			}
			if (x_other_way == -1 && y_other_way == -1) y_other_way = 1;



			ViewModule vm = ViewModule(mod, sf::Vector2f(base_position.first + x_other_way * (i + 1) * Drawer::SPRITE_SIZE.first + Drawer::SPRITE_SIZE.first / 4, base_position.second + Drawer::SPRITE_SIZE.second / 4), "", sf::Vector2f(0, 0), sf::Vector2f(0.1, 0.1));
			vm.draw();
			vm.inventoryView.sprite.setPosition(sf::Vector2f(base_position.first + x_other_way * (i + 1) * sprite.first, y_other_way * base_position.second));
			ViewModule vm_big = vm;
			vm_big.sprite.setPosition(Drawer::TOP_RIGHT_CORNER);
			vm_big.sprite.setScale(Drawer::SPRITE_SCALE);

			modules.push_back({vm, vm_big});
		}
	}
}