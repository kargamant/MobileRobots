#include <iostream>

int main()
{
	std::system("lcov -t \"test-testing\" -o test-testing.info -c -d .");
	std::system("genhtml -o report test-testing.info");	
	return 0;
}
