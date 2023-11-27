#include "ViewCell.h"
#include "../Field/Cell.h"

namespace Game
{
    std::string ViewCell::GROUND_TEXTURE = "ground.jpg";
    std::string ViewCell::OBSTACLE_TEXTURE = "obstacle.png";
    std::string ViewCell::POI_TEXTURE = "poi.jpg";

	void ViewCell::draw()
	{
        description.setString(std::format("({}, {}) : {}", std::to_string(cell->getX()), std::to_string(cell->getY()), Field::CellTypeToString(cell->getType())));
        texture->loadFromFile(RESOURCES_PATH+"/" + cellToFileName(*cell));
        sprite.setTexture(*texture);
	}

    std::string ViewCell::cellToFileName(Field::Cell& cell)
    {
        std::string filename;
        switch (cell.getType())
        {
        case Field::CellType::ground:
            filename = GROUND_TEXTURE;
            break;
        case Field::CellType::obstacle:
            filename = OBSTACLE_TEXTURE;
            break;
        case Field::CellType::pointOfInterest:
            filename = POI_TEXTURE;
            break;
        }
        //if (field->checkPlatformOnField(coordinates) != nullptr) filename = ROBOT_TEXTURE;
        return filename;
    }
}