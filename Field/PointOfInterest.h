#include "Cell.h"

namespace Field
{
	class PointOfInterest :public Cell
	{
	private:
		int id;
		bool isDiscovered;
	public:
		PointOfInterest(id, std::pair<int, int> coordinates);

		int getId() { return id; }
		PointOfInterest& setId(int nid) { id = nid; return *this; }
		bool isDiscovered() { return isDiscovered; }

		void Discover() { isDiscovered = true; }
	};
}