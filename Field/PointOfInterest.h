#include "Cell.h"

namespace Field
{
	class PointOfInterest :public Cell
	{
	private:
		int id;
		bool isDiscovered;
	public:
		int getId() { return id; }
		void Discover() { isDiscovered = true; }
	};
}