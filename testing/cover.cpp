#include <iostream>
#include <string>
#include <vector>
#include <format>

int main()
{
	std::vector<std::string> build_dirs = {"Field", "Interfaces", "Modules", "Platforms", "testing"};
	for (auto dir : build_dirs)
	{
		std::string gcno_command = std::format("find ../build/{}/CMakeFiles/{}.dir -name \"*.gcno\" -exec ", dir, dir);
		std::string gcda_command = std::format("find ../build/{}/CMakeFiles/{}.dir -name \"*.gcda\" -exec ", dir, dir);
		gcno_command += "cp {} gc_info \\;";
		gcda_command += "cp {} gc_info \\;";
		std::cout << gcno_command << std::endl;
		std::system(gcno_command.c_str());
		std::system(gcda_command.c_str());
	}
	std::system("lcov -t \"test-testing\" -o test-testing.info -c -d gc_info");
	std::system("genhtml -o report test-testing.info");	
	return 0;
}
