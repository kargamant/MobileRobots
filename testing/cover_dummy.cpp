#include <iostream>
#include <string>
#include <vector>
#include <format>

int main()
{
	std::system("lcov -t \"test-testing\" -o test-testing.info -c -d gc_info");
	std::system("genhtml -o report test-testing.info");	
	return 0;
}
