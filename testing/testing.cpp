#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../Interfaces/Platform.h"
#include "../Field/Field.h"
#include "../MyUnorderedMap/MyUnorderedMap.h"
#include "../Platforms/RobotCommander.h"

typedef MyUnorderedMap<std::pair<int, int>, Robots::Platform*, Field::CoordHash, Field::CoordEqual> field_map;

std::pair<Item<field_map::value_type>*, Item<field_map::value_type>*> generateItemVec(int n)
{
	//std::vector<Item<field_map::value_type>*> result;
	Item<field_map::value_type>* last = nullptr;
	Item<field_map::value_type>* first = nullptr;
	Item<field_map::value_type>* prev = nullptr;
	for (int i = 0; i < n; i++)
	{
		Robots::Platform* plt = new Robots::RobotCommander();
		plt->setCoordinates(i, i);
		Item<field_map::value_type>* ptr = new Item<field_map::value_type>(field_map::value_type({ plt->getCoordinates(), plt }));
		if (prev != nullptr) prev->next = ptr;
		else first = ptr;
		prev = ptr;
		if (i == (n-1)) last = ptr;
		//result.push_back(ptr);
		std::cout << "db1" << std::endl;
	}
	return {first, last};
}


TEST_CASE("MyUnorderedMap")
{
	SECTION("empty constructor")
	{
		field_map um{};
		field_map::size_type def = field_map::DEFAULT_BUCKET_COUNT;
		REQUIRE(um.mbc == def);
	}
	SECTION("iterator range constructor")
	{
		Item<field_map::value_type>* last = nullptr;
		Item<field_map::value_type>* first = nullptr;
		Item<field_map::value_type>* prev = nullptr;

		std::vector<Robots::Platform*> platforms;
		for (int i = 0; i < 10; i++)
		{
			Robots::Platform* plt = new Robots::RobotCommander();
			plt->setCoordinates(i, 0);
			if (i != 9) platforms.push_back(plt);
			Item<field_map::value_type>* ptr = new Item<field_map::value_type>(field_map::value_type({ plt->getCoordinates(), plt }));
			if (prev != nullptr) prev->next = ptr;
			else first = ptr;
			prev = ptr;
			if (i == 9) last = ptr;
		}
		field_map um{ field_map::iterator(first), field_map::iterator(last) };
		for (auto pr : platforms)
		{
			if (pr->getCoordinates().first != 9) REQUIRE(um.contains(pr->getCoordinates()));
		}
		
		/*ﬂ ¬¿’”≈ ¡Àﬂ“‹, ŒÕŒ ¬€«€¬¿≈“  ŒÕ—“–” “Œ– Õ≈— ŒÀ‹ Œ –¿«  ¿ Œ√Œ ’”ﬂ ¡Àﬂ“‹
		std::pair<Item<field_map::value_type>*, Item<field_map::value_type>*> items = generateItemVec(10);
		field_map::iterator last = field_map::iterator(items.second);
		field_map::iterator first = field_map::iterator(items.first);
		field_map um{ first, last};
		field_map::iterator ir = first;
		while (ir != last)
		{
			if(ir.it->value.first.first!=9) REQUIRE(um.contains(ir.it->value.second->getCoordinates()));
			++ir;
		}*/
		/*for (auto itr : items)
		{
			//std::cout << "db2" << std::endl;
			if(itr->value.second->getCoordinates().first!=9) REQUIRE(um.contains(itr->value.second->getCoordinates()));
		}*/

		//partial freeing. Platforms aren't cleaned because of some bugg in destructor
		field_map::iterator itr = field_map::iterator(first);
		while (itr != field_map::iterator(last))
		{
			field_map::iterator next = field_map::iterator(itr.it->next);
			delete itr.it;
			itr = next;
		}
	}
	SECTION("insert by initializer list")
	{
		field_map um{};
		Robots::Platform* plt = new Robots::RobotCommander();
		um.insert({ {{1, 2}, plt} });
		REQUIRE(um[{1, 2}]==plt);
		REQUIRE(um.begin().it->value.second == plt);
		REQUIRE(++um.begin() == um.end());
	}
	SECTION("insert by iterator range")
	{
		field_map um{};
		Item<field_map::value_type>* last = nullptr;
		Item<field_map::value_type>* first = nullptr;
		Item<field_map::value_type>* prev = nullptr;
		
		std::vector<Robots::Platform*> platforms;
		for (int i = 0; i < 10; i++)
		{
			Robots::Platform* plt = new Robots::RobotCommander();
			plt->setCoordinates(i, 0);
			if(i!=9) platforms.push_back(plt);
			Item<field_map::value_type>* ptr = new Item<field_map::value_type>(field_map::value_type({plt->getCoordinates(), plt}));
			if (prev != nullptr) prev->next = ptr;
			else first = ptr;
			prev = ptr;
			if (i == 9) last = ptr;
		}

		um.insert(field_map::iterator(first), field_map::iterator(last));

		field_map::iterator itr = um.begin();
		int k = 0;
		while (itr != um.end())
		{
			itr.it->value.second->consoleOut();
			k++;
			++itr;
		}
		REQUIRE(k == 9);

		for (auto pr : platforms)
		{
			REQUIRE(um.contains(pr->getCoordinates()));
		}

		//partial freeing. Platforms aren't cleaned because of some bugg in destructor
		field_map::iterator itr2 = field_map::iterator(first);
		while (itr2 != field_map::iterator(last))
		{
			field_map::iterator next = field_map::iterator(itr2.it->next);
			delete itr2.it;
			itr2 = next;
		}
	}
}