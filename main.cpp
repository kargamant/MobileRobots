#include "Field/Field.h"

int Field::Field::MAX_RANDOM_SIZE = 100;

int main()
{
	Field::Field::MAX_RANDOM_SIZE = 50;
	Field::Field fld=Field::Field();
	fld.consoleOutField();
	fld.resize(fld.getWidth()/2, fld.getHeight()/2);
	fld.consoleOutField();
	return 0;
}