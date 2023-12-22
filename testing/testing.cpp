#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../Interfaces/Platform.h"
#include "../Field/Field.h"
#include "../MyUnorderedMap/MyUnorderedMap.h"

TEST_CASE("MyUnorderedMap")
{
	SECTION("constructor")
	{
		Field::Field fld=Field::Field(10, 10);
		MyUnorderedMap<int, std::string> um(10);
	}
}