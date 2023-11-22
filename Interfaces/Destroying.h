#include "Platform.h"
#include "../Field/Field.h"

namespace Robots
{
	class Destroying : virtual public Platform
	{
	private:
		int max_radius;
	public:
		Destroying(int max_rad = 1, double energy = 0, int slots = 1, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0)) : max_radius(max_rad), Platform(energy, slots, cost, coordinates) {}
		
		int getMaxRadius() { return max_radius; }
		Destroying& setMaxRadius(int nrad) { max_radius = nrad; return *this; }
		
		virtual void destroy(Field::Field* fld, std::pair<int, int> coordinates)=0; 
	};
}