#include "Drawer.h"
#include "../Field/Cell.h"

class ViewCell :public View
{
private:
	Field::Cell& cell;
public:
	void mouseClick(Drawer dr, sf::Event event)
	{
        std::pair<std::pair<int, int>, sf::Sprite> closest_cell = dr.mouseClick(event);
        if (closest_cell.first.first != -1 && closest_cell.first.second != -1)
        {
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
        }
        //std::cout << closest_cell.first.first << " " << closest_cell.first.second << std::endl;
        
	}
};