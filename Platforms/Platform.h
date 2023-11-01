#include "Cell.h"
#include "Module.h"
using namespace Field;

namespace Robots
{
	class Platform : public Cell 
	{
	private:
		std::string name;
		double energyLevel; //level of consumption
		int slots;
		int cost;
		Module* robo;
	public:
		Platform(double energy, int slots, int cost, std::pair coordinates); //name will be chosen randomly
		Platform(std::string name, double energy, int slots, int cost, std::pair coordinates);
		Platform(double energy, int slots, int cost, Cell& cell);
		Platform(std::string name, double energy, int slots, int cost, Cell& cell);
		Platform(Platform& plt);
		
		int getSlots() { return slots; }
		double getEnergyLevel() { return energyLevel; }
		int getCost() { return cost; }
		std::string getName() { return name; }

		Platform& setName(std::string nname);
		Platform& setEnergyLevel(double nenergy);
		Platform& setSlots(int slots);
		Platform& setCost(int cost);

		void deleteRobo(int ind);
		void placeRobo(int ind);
		void turnOn(int ind);
		void turnOff(int ind);
	};
}