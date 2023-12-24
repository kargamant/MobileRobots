#include "../Field/Cell.h"
#include "../Modules/Module.h"
#include <string>
#include <vector>
#include <fstream>
#pragma once

namespace Robots
{
	std::string randomRoboName(std::fstream& file);
	std::string priorityToString(Priority pr);
	
	/*!
	 extensible Platform class. All robots are inherited from here.
	*/
	class Platform
	{
	protected:
		Priority roboPriority;
		static std::string NICKNAME_FILENAME;
		std::string name;
		Platform* master = nullptr;
		bool isMaster = false;
		std::pair<int, int> coordinates;
		double energyLevel; //level of consumption
		int slots;
		int cost;
		std::vector<Module*> robo;
		void checkInd(int ind);
	public:
		bool isDynamic = false;
		/*!
		Basic constructor for platform, but name is being chosen randomly.
		@param double energy - energy consumption level of a platform.
		@param int slots - threshold of slots that you can place on this platform.
		@param int cost - number of tokens needed to buy this platform in sand box mode.
		@param std::pair<int, int> coordinates - coordinates of platform.
		*/
		Platform(double energy, int slots, int cost, std::pair<int, int> coordinates);

		/*!
		Basic constructor for platform
		@param std::string name - nickname that will be assigned to platform.
		@param double energy - energy consumption level of a platform.
		@param int slots - threshold of slots that you can place on this platform.
		@param int cost - number of tokens needed to buy this platform in sand box mode.
		@param std::pair<int, int> coordinates - coordinates of platform.
		*/
		Platform(std::string name=std::string("c3po"), double energy=0, int slots=1, int cost=1000, std::pair<int, int> coordinates=std::pair<int, int>(0, 0));

		~Platform(){}

		/*!
		Slots getter
		@returns slots
		*/
		int getSlots() { return slots; }

		/*!
		coordinates getter
		@returns coordinates
		*/
		std::pair<int, int>& getCoordinates() { return coordinates; }

		/*!
		x coordinate getter
		@returns x coordinate
		*/
		int getX() { return coordinates.first; }

		/*!
		y coordinate getter
		@returns y coordinate
		*/
		int getY() { return coordinates.second; }

		/*!
		energy level getter
		@returns energy level
		*/
		double getEnergyLevel() { return energyLevel; }//flash

		/*!
		cost getter
		@returns cost
		*/
		int getCost() { return cost; }

		/*!
		nickname getter
		@returns name
		*/
		std::string getName() { return name; }

		/*!
		getter of vector that stores modules pointers placed on this platform.
		@returns vector of modules aka robo
		*/
		std::vector<Module*> getRobo() { return robo; }

		/*!
		operator[] overload for getRobo method
		@returns module pointer that corresponds to given index
		@throws std::invalid_argument if given index is out of range or incorrect.
		*/
		Module* operator[](int ind) { if (ind < 0 || ind >= robo.size()) throw std::invalid_argument("Error. No module with such index."); return getRobo()[ind]; }
		
		/*!
		getter of master pointer - pointer to rulling platform that subdued current. 
		If this platform is rulling, master should remain nullptr at runtime.
		Otherwise behaviour is undefined.
		@returns pointer to master
		*/
		Platform* getMaster() { return master; }

		/*!
		getter of flag isMaster.
		isMaster is true, if platform is rulling and false otherwise.
		@returns isMaster flag
		*/
		bool getIsMaster() { return isMaster; }

		/*!
		getter of robo priority. 
		It could be one of the following: high, medium, low.(consider that this value is of enum class Priority)
		Used mostly in ai playing algorithm.
		@returns priority
		*/
		Priority getRoboPriority() { return roboPriority; }

		/*!
		nickname setter
		@param std::string nname
		@returns *this
		*/
		Platform& setName(std::string nname) { name = nname; return *this; }

		/*!
		energy level setter
		@param std::string nenergy
		@returns *this
		@throws std::invalid_argument - if negative param is given.
		*/
		Platform& setEnergyLevel(double nenergy) { if (nenergy < 0) throw std::invalid_argument("Error. energy level cant be negative."); energyLevel = nenergy; return *this; }

		/*!
		Slots setter
		@param std::string nslots
		@returns *this
		@throws std::invalid_argument - if negative param is given.
		*/
		Platform& setSlots(int nslots) { if (nslots < 0) throw std::invalid_argument("Error. number of slots cant be negative."); slots = nslots; return *this; }

		/*!
		cost setter
		@param std::string ncost
		@returns *this
		@throws std::invalid_argument - if negative param is given.
		*/
		Platform& setCost(int ncost) { if (ncost < 0) throw std::invalid_argument("Error. cost cant be negative."); cost = ncost; return *this; }

		/*!
		coordinates setter
		@param int x
		@param int y
		@returns *this
		*/
		Platform& setCoordinates(int x, int y) { coordinates.first = x; coordinates.second = y; return *this; }

		/*!
		setter of master pointer - pointer to rulling platform that subdued current.
		If this platform is rulling, master should remain nullptr at runtime.
		Otherwise behaviour is undefined.
		@param Platform* nmaster
		@returns *this
		*/
		Platform& setMaster(Platform* nmaster) { master = nmaster; return *this; }
		
		/*!
		stream output method.
		@param std::ostream& stream - stream to output platform. By default set to std::cout.
		*/
		void consoleOut(std::ostream& stream = std::cout);

		/*!
		deletes module from platform by index.
		@param int ind
		@throws std::invalid_argument - if given index is incorrect or if module corresponding to index ind is manage module and platform is rulling.
		*/
		virtual void deleteModule(int ind);

		/*!
		deletes module from platform by pointer.
		@param Module* mod
		@throws std::invalid_argument - if there is no such pointer in robo vector or if module is manage module and platform is rulling.
		*/
		virtual void deleteModule(Module* mod);

		/*!
		places module on a certain position.
		@param int ind - position to place module.
		@param Module& mod - reference to a module to be placed.
		@throws std::invalid_argument - if index is incorrect or if module is manage module and platform is rulling.
		*/
		virtual void placeModule(int ind, Module& mod);

		/*!
		places module to the back of the robo vector.
		@param Module& mod - reference to a module to be placed.
		@throws std::invalid_argument - if module is manage module and platform is rulling.
		*/
		virtual void placeModule(Module& mod);

		/*!
		turns module corresponding to index ind On.
		@param int ind - index of module to turn on.
		@throws std::invalid_argument - if module is not connected to power or there is not enough energy supply of generator. Or simply because index is incorrect.
		*/
		virtual void turnOn(int ind);

		/*!
		turns module corresponding to index ind Off.
		@param int ind - index of module to turn off.
		@throws std::invalid_argument - if index is incorrect.
		*/
		virtual void turnOff(int ind);

		/*!
		turns module by pointer On.
		@param Module* mod - pointer to module to turn on.
		@throws std::invalid_argument - if module is not connected to power or there is not enough energy supply of generator. Or because there is no such module on this platform.
		*/
		virtual void turnOn(Module* mod);

		/*!
		turns module by pointer Off.
		@param Module* mod - pointer to module to turn off.
		@throws std::invalid_argument - if there is no such module on this platform.
		*/
		virtual void turnOff(Module* mod);
	};

}