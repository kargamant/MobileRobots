#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../Interfaces/Platform.h"
#include "../Field/Field.h"
#include "../MyUnorderedMap/MyUnorderedMap.h"
#include "../Platforms/RobotCommander.h"

typedef MyUnorderedMap<std::pair<int, int>, Robots::Platform*, Field::CoordHash, Field::CoordEqual> field_map;

TEST_CASE("MyUnorderedMap")
{
	SECTION("empty constructor")
	{
		field_map um{};
		field_map::size_type def = field_map::DEFAULT_BUCKET_COUNT;
		REQUIRE(um.mbc == def);
	}
	SECTION("insert")
	{
		field_map um{};
		Robots::Platform* plt = new Robots::RobotCommander();
		um.insert({ {{1, 2}, plt} });
		//std::cout << "is itr null: " << (um.end().it == nullptr) << std::endl;
		REQUIRE(um[{1, 2}]==plt);
		REQUIRE(um.begin().it->value.second == plt);
		REQUIRE(++um.begin() == um.end());
		
	}
}