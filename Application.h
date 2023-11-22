#include "Field/Field.h"
#include "ArtificialIntelligence.h"
#include <fstream>
using namespace Field;
using namespace Robots;

namespace Game
{
	class Application
	{
	private:
		Field::Field field;
		ArtificialIntelligence ai;
	public:
		Application(Field& fld, ArtificialIntelligence& ai);
		Application(); //in this case Field will be totally random
		Application(int width, int height);
		Application(int width, int height, Cell** map, std::vector<Platform> plt)

		void loadFieldFromFile(std::string filename, std::fstream& stream);

		void play(); //starts game
	};
}