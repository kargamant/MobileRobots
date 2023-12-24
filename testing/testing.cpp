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
			if(!itr.it->isEnd)k++;
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

		
	}
	SECTION("erase")
	{
		field_map um{};
		Item<field_map::value_type>* last = nullptr;
		Item<field_map::value_type>* first = nullptr;
		Item<field_map::value_type>* prev = nullptr;
		Item<field_map::value_type>* mid = nullptr;

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
			if (i == 4) mid = ptr;
		}

		um.insert(field_map::iterator(first), field_map::iterator(last));

		um.erase({ 0, 0 });
		REQUIRE(!um.contains({ 0, 0 }));
		REQUIRE(um.size() == 8);
		um.erase(um.find(platforms[8]->getCoordinates()));
		REQUIRE(!um.contains({8, 0}));
		REQUIRE(um.size() == 7);
		um.erase(um.find({1, 0}), um.find({1, 0}));
		REQUIRE(um.contains({ 1, 0 }));
		um.erase(um.find({ 1, 0 }), um.find({ 2, 0 }));
		REQUIRE(!um.contains({ 1, 0 }));
		REQUIRE(!um.contains({ 6, 0 }));
		REQUIRE(um.contains({ 2, 0 }));
		REQUIRE(um.erase({ 5, 0 })==1);
		REQUIRE_THROWS(um.erase(um.find({ 5, 0 })));
		REQUIRE(!um.contains({ 5, 0 }));
		um.clear();
		REQUIRE(um.bc == 0);
		REQUIRE(um.begin() == um.end());
	}
	SECTION("getters setters")
	{
		field_map um{};
		REQUIRE(um.empty());
		REQUIRE(um.bucket_count() == um.bc);
		REQUIRE(um.max_bucket_count() == um.mbc);
		Robots::Platform plt = Robots::RobotDestroyer();
		Robots::Platform plt2 = Robots::RobotDestroyer();
		Robots::Platform plt3 = Robots::RobotDestroyer();
		um.insert({ {{1, 2}, &plt}, {{2, 2}, &plt2}, {{3, 2}, &plt3} });
		REQUIRE(um.size() == 3);
		REQUIRE(um.bucket_size(5)==1);
	}
	SECTION("iterator base methods")
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
			if (i != 9) platforms.push_back(plt);
			Item<field_map::value_type>* ptr = new Item<field_map::value_type>(field_map::value_type({ plt->getCoordinates(), plt }));
			if (prev != nullptr) prev->next = ptr;
			else first = ptr;
			prev = ptr;
			if (i == 9) last = ptr;
		}

		um.insert(field_map::iterator(first), field_map::iterator(last));
		field_map::iterator itr1 = um.find({ 1, 0 });
		field_map::iterator itr2 = um.find({ 2, 0 });
		REQUIRE((*itr1).second == platforms[1]);
		itr1 = itr2;
		REQUIRE(itr1 == itr2);
		field_map::iterator itr3 = um.find({ 3, 0 });
		field_map::iterator nitr{std::move(itr3)};
		REQUIRE(nitr.operator->()->second==platforms[3]);
		REQUIRE(itr3.it == nullptr);
		field_map::iterator nitr2{ itr1 };
		REQUIRE(nitr2 == itr1);
	}
}

TEST_CASE("Field class")
{
	SECTION("constructors and getters/setters")
	{
		Field::Field fld{10, 10};
		REQUIRE(fld.getWidth() == 10);
		REQUIRE(fld.getHeight() == 10);
		Field::Field fld2{};
		REQUIRE(fld2.getSize().first < 5+Field::Field::MAX_RANDOM_SIZE);
		REQUIRE(fld2.getSize().second < 5+Field::Field::MAX_RANDOM_SIZE);

		Field::Field::GROUND_MODE_ON = true;
		Field::Field fld3{};
		for (int i = 0; i < fld3.getWidth(); i++)
		{
			for (int j = 0; j < fld3.getHeight(); j++)
			{
				REQUIRE(fld3.getCellByCoordinates(i, j).getType() == Field::CellType::ground);
			}
		}
		fld.changeCellType({ 1, 2 }, Field::CellType::obstacle);
		REQUIRE(fld.getCellByCoordinates({ 1, 2 }).getType() == Field::CellType::obstacle);
		REQUIRE_THROWS(fld.changeCellType(100, 10, Field::CellType::pointOfInterest));
	}
	SECTION("resize")
	{
		Field::Field::GROUND_MODE_ON = false;
		Field::Field fld{ 10, 10 };
		Field::Field::GROUND_MODE_ON = true;
		fld.resize(15, 15);
		REQUIRE(fld.getWidth() == 15);
		REQUIRE(fld.getHeight() == 15);
		for (int i = 10; i < 15; i++)
		{
			for (int j = 10; j < 15; j++)
			{
				
				REQUIRE(fld.getCellByCoordinates(i, j).getType() == Field::CellType::ground);
				REQUIRE(fld.getCellByCoordinates(j, i).getType() == Field::CellType::ground);
			}
		}
		fld.resize({ 8, 8 });
		for (int i = 8; i < 15; i++)
		{
			for (int j = 8; j < 15; j++)
			{
				REQUIRE_THROWS(fld.getCellByCoordinates(i, j));
				REQUIRE_THROWS(fld.getCellByCoordinates(j, i));
			}
		}
		REQUIRE(fld.getWidth() == 8);
		REQUIRE(fld.getHeight() == 8);
	}
	SECTION("Platform placement, moving and erasing")
	{
		Field::Field::GROUND_MODE_ON = false;
		Field::Field fld{ 10, 10 };
		Robots::Platform plt = Robots::RobotCommander();
		plt.setCoordinates(1, 1);
		fld.placePlatform(&plt);
		REQUIRE(fld.checkPlatformOnField({ 1, 1 }) == &plt);
		Robots::Platform plt2 = Robots::RobotDestroyer();
		plt2.setCoordinates(1000, 1000);
		REQUIRE_THROWS(fld.placePlatform(&plt2));

		fld.changeCellType({ 3, 3 }, Field::CellType::ground);
		fld.movePlatform({ 1, 1 }, { 2, 2 });
		REQUIRE(fld.checkPlatformOnField({ 1, 1 }) == nullptr);
		REQUIRE(fld.checkPlatformOnField({ 3, 3 }) == &plt);
		REQUIRE_THROWS(fld.movePlatform({ 3, 3 }, { 1000, 1 }));
		int old_total = fld.total_poi;
		fld.changeCellType({ 3, 5 }, Field::CellType::pointOfInterest);
		REQUIRE(old_total < fld.total_poi);
		fld.movePlatform({ 3, 3 }, { 0, 2 });
		REQUIRE(old_total == fld.total_poi);

		fld.erasePlatform(&plt);
		REQUIRE(fld.checkPlatformOnField({ 2, 2 }) == nullptr);
		REQUIRE_THROWS(fld.erasePlatform({ 1000, 2 }));
	}
	SECTION("cell destruction")
	{
		Field::Field::GROUND_MODE_ON = false;
		Field::Field fld{ 10, 10 };
		fld.changeCellType({ 1, 8 }, Field::CellType::obstacle);
		fld.destroyCell({ 1, 8 });
		REQUIRE(fld.getCellByCoordinates({ 1, 8 }).getType() == Field::CellType::ground);
		fld.destroyCell({ 1, 8 });
		REQUIRE(fld.getCellByCoordinates({ 1, 8 }).getType() == Field::CellType::ground);
		REQUIRE_THROWS(fld.destroyCell({1, 10}));

		fld.destroyArea(1, { 0, 0 });
		REQUIRE(fld.getCellByCoordinates({ 0, 1 }).getType() != Field::CellType::obstacle);
		REQUIRE(fld.getCellByCoordinates({ 1, 0 }).getType() != Field::CellType::obstacle);
		REQUIRE(fld.getCellByCoordinates({ 1, 1 }).getType() != Field::CellType::obstacle);
	}
}