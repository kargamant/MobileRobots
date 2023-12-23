#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../Interfaces/Platform.h"
#include "../Field/Field.h"
#include "../MyUnorderedMap/MyUnorderedMap.h"
#include "../Platforms/RobotCommander.h"
#include "../Platforms/RobotDestroyer.h"

typedef MyUnorderedMap<std::pair<int, int>, Robots::Platform*, Field::CoordHash, Field::CoordEqual> field_map;

Item<field_map::value_type>* generateItemVec(int n)
{
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
	}
	return first;
}


TEST_CASE("MyUnorderedMap")
{
	SECTION("default constructor")
	{
		field_map um{};
		field_map::size_type def = field_map::DEFAULT_BUCKET_COUNT;
		REQUIRE(um.mbc == def);
	}
	SECTION("standard constructor with arguments")
	{
		field_map um{ 20 };
		REQUIRE(um.mbc==20);
		Robots::Platform plt = Robots::RobotDestroyer();
		um.insert({ {2, 3},  &plt.setCoordinates(2, 3)});
		REQUIRE(um.bc == 1);
		REQUIRE(um.contains({ 2, 3 }));
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
		
		/*
		//Some wierd shit
		//Constructor called multiple times wtf
		Item<field_map::value_type>* first = generateItemVec(10);
		Item<field_map::value_type>* ptr = first;
		while (ptr->next != nullptr)
		{
			ptr->value.second->consoleOut();
			ptr = ptr->next;
		}
		Item<field_map::value_type>* last = ptr;
		field_map um{ field_map::iterator(first), field_map::iterator(last)};
		field_map::iterator ir = field_map::iterator(first);
		while (ir != field_map::iterator(last))
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
			//delete itr.it->value.second;
			delete itr.it;
			itr = next;
		}
	}
	SECTION("Copy constructor")
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
		field_map um2{ um };
		field_map::iterator itr = um.begin();
		while (itr != um.end())
		{
			REQUIRE(um2.find(itr.it->value.first)!=um2.end());
			++itr;
		}

		field_map::iterator it = field_map::iterator(first);
		while (it != field_map::iterator(last))
		{
			field_map::iterator next = field_map::iterator(it.it->next);
			//delete it.it->value.second;
			delete it.it;
			it = next;
		}
	}
	SECTION("Move constructor")
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
		field_map tmp{ um };
		field_map um2{ std::move(um) };
		field_map::iterator itr = tmp.begin();
		while (itr != tmp.end())
		{
			REQUIRE(um2.contains(itr.it->value.first));
			++itr;
		}
		REQUIRE(um.buckets==nullptr);
		REQUIRE(um.before_begin==nullptr);
		REQUIRE(um.past_the_last==nullptr);
		REQUIRE(um.bc==0);
		REQUIRE(um.mbc==0);
		REQUIRE(um.last_added_bucket==-1);
	}
	SECTION("initializer list constructor")
	{
		Robots::Platform* plt1 = new Robots::RobotDestroyer();
		Robots::Platform* plt2 = new Robots::RobotCommander();
		field_map um{ { {{1, 3}, &plt1->setCoordinates(1, 3)}, {{2, 5}, &plt2->setCoordinates(2, 5)} } };
		field_map::size_type def = field_map::DEFAULT_BUCKET_COUNT;
		REQUIRE(um.mbc == def);
		//um.try_emplace({ 2, 5 }, plt1);
		REQUIRE(!um.try_emplace({2, 5}, plt1).second);
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
			//itr.it->value.second->consoleOut();
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
	SECTION("insert or assign")
	{
		field_map um{};
		Robots::Platform plt = Robots::RobotCommander();
		plt.setCoordinates(1, 3);
		Robots::Platform plt2 = Robots::RobotDestroyer();
		plt2.setCoordinates(1, 3);
		um.insert({ {plt.getCoordinates(), &plt} });
		um.insert_or_assign(plt2.getCoordinates(), &plt2);
		REQUIRE(um.find({1, 3}).it->value.second==&plt2);
	}
	SECTION("emplace")
	{
		field_map um{};
		Robots::Platform plt = Robots::RobotDestroyer();
		um.emplace(std::make_pair(std::pair<int, int>(2, 5) , &plt));
		REQUIRE(um.find({2, 5}).it->value.second==&plt);
	}
	SECTION("emplace hint")
	{
		field_map um{};
		Robots::Platform plt = Robots::RobotCommander();
		plt.setCoordinates(1, 3);
		Robots::Platform plt2 = Robots::RobotDestroyer();
		plt2.setCoordinates(5, 1);
		um.emplace(std::make_pair(plt.getCoordinates(), &plt));
		um.emplace(std::make_pair(plt2.getCoordinates(), &plt2));
		Robots::Platform plt3 = Robots::RobotDestroyer();
		plt3.setCoordinates(5, 1);
		REQUIRE(um.emplace_hint(um.find({ 5, 1 }), std::make_pair(plt3.getCoordinates(), &plt3)) == um.end());
		plt3.setCoordinates(0, 8);
		REQUIRE(um.emplace_hint(um.find({ 5, 1 }), std::make_pair(plt3.getCoordinates(), &plt3)) != um.end());
		REQUIRE(um.contains(plt.getCoordinates()));
		REQUIRE(um.contains(plt2.getCoordinates()));
		REQUIRE(um.contains(plt3.getCoordinates()));
	}
	SECTION("extract")
	{
		field_map um{};
		Robots::Platform plt = Robots::RobotCommander();
		plt.setCoordinates(1, 3);
		um.insert({ {plt.getCoordinates(), &plt} });
		field_map::node_type* node = um.extract(plt.getCoordinates());
		REQUIRE(node->value.second==&plt);
		field_map::iterator itr = um.find({ 1, 3 });

		REQUIRE(um.find({ 1, 3 }) == um.end());

		/*Robots::Platform plt2 = Robots::RobotDestroyer();
		plt2.setCoordinates(0, 1);
		um.insert({ {plt.getCoordinates(), &plt}, {plt2.getCoordinates(), &plt2}});
		REQUIRE(um.bucket({ 1, 3 }) == um.bucket({0, 1}));
		field_map::node_type* node2 = um.extract(um.find({0, 1}, true));
		REQUIRE(node2->value.second==&plt2);
		REQUIRE(um.find({ 0, 1 }) == um.end());
		REQUIRE(um.find({ 1, 3 }) != um.end());
		REQUIRE(um.size()==1);*/
	}
	SECTION("erase")
	{
		
	}
}