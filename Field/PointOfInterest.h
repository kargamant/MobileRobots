#include "Cell.h"

namespace Field
{
	class PointOfInterest :public Cell
	{
	private:
		int id;
		bool isDiscovered;
	public:
		PointOfInterest(id, std::pair coordinates);
		PointOfInterest(id, Cell& cell);

		int getId() { return id; }
		void Discover() { isDiscovered = true; }
	};
}