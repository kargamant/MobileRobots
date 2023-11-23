#include "Dialogue.h"

namespace Dialogue
{
	int getMoney()
	{
		std::cout << "Enter an amount of money you want to start build up with: ";
		return getOpt(0);
	}
}