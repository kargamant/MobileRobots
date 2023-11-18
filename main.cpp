#include "Field/Field.h"

int Field::Field::MAX_RANDOM_SIZE = 10;

int main()
{
	Field::Field fld=Field::Field();
	Robots::Moving* plt1 = new Robots::Moving();
	fld.placePlatform(plt1);
	fld.consoleOutField();
	fld.movePlatform({ 0, 0 }, {1, 1});
	std::cout << std::endl;
	fld.consoleOutField();
	//std::cout << fld.getPlatforms()[std::pair<int, int>(0, 0)].getName() << std::endl;
	return 0;
}