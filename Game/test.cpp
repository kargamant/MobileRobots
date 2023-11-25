#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
	std::unordered_map<int, std::string> table1=
	{
		{1, "coffee"}, {2, "tea"}, {2, "water"}
	};
	std::cout<<table1[2]<<std::endl;
	table1.insert({2, "milk"});
	std::cout<<table1[2]<<std::endl;
	table1.erase(2);
	std::cout<<table1[2]<<std::endl;

	return 0;
}
