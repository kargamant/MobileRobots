#include "../Field/Cell.h"
#include "../Modules/Module.h"
#include <string>
#include <vector>
#include <fstream>
#pragma once

namespace Robots
{
	std::string randomRoboName(std::fstream& file);
	class Platform
	{
	protected:
		static std::string NICKNAME_FILENAME;
		std::string name;
		Platform* master = nullptr;
		std::pair<int, int> coordinates;
		double energyLevel; //level of consumption
		int slots;
		int cost;
		std::vector<Module*> robo;
		void checkInd(int ind);
	public:
		Platform(double energy, int slots, int cost, std::pair<int, int> coordinates); //name will be chosen randomly
		Platform(std::string name=std::string("c3po"), double energy=0, int slots=1, int cost=0, std::pair<int, int> coordinates=std::pair<int, int>(0, 0));

		int getSlots() { return slots; }
		std::pair<int, int>& getCoordinates() { return coordinates; }
		int getX() { return coordinates.first; }
		int getY() { return coordinates.second; }
		double getEnergyLevel() { return energyLevel; }//flash
		int getCost() { return cost; }
		std::string getName() { return name; }
		std::vector<Module*> getRobo() { return robo; }
		Module* operator[](int ind) { return getRobo()[ind]; }
		Platform* getMaster() { return master; }

		Platform& setName(std::string nname) { name = nname; return *this; }
		Platform& setEnergyLevel(double nenergy) { energyLevel = nenergy; return *this; }
		Platform& setSlots(int nslots) { slots = nslots; return *this; }
		Platform& setCost(int ncost) { cost = ncost; return *this; }
		Platform& setCoordinates(int x, int y) { coordinates.first = x; coordinates.second = y; return *this; }
		Platform& setMaster(Platform* nmaster) { master = nmaster; return *this; }

		virtual void deleteModule(int ind);
		virtual void placeModule(int ind, Module& mod);
		virtual void placeModule(Module& mod);
		void turnOn(int ind);
		void turnOff(int ind);
	};

}