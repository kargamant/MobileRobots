#include "Platform.h"

namespace Robots
{
	class Destroying : public Platform
	{
	public:
		virtual void destroy(int radius);
	};
}