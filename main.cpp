#include "Field/Field.h"

int Field::Field::MAX_RANDOM_SIZE = 100;

int main()
{
	Field::Field::MAX_RANDOM_SIZE = 50;
	Field::Field fld=Field::Field();
	Robots::Platform plt1 = Robots::Platform(0.0, 5, 1000, { 0, 0 });
	fld.placePlatform(plt1);
	fld.consoleOutField();
	//std::cout << fld.getPlatforms()[std::pair<int, int>(0, 0)].getName() << std::endl;
	return 0;
}