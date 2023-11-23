#include "Field/Field.h"
#include "ArtificialIntelligence.h"
#include <fstream>
//using namespace Field;
//using namespace Robots;

namespace Game
{
	class Application
	{
	private:
		Field::Field field;
		Robots::ArtificialIntelligence ai;
	public:
		Application(Field::Field& fld, Robots::ArtificialIntelligence& ai) : field(fld), ai(ai) {}
		Application() : field(Field::Field()), ai(ArtificialIntelligence()) {} //in this case Field will be totally random
		Application(int width, int height) : field(width, height), ai(ArtificialIntelligence()) {}
		//Application(int width, int height, std::vector<std::vector<Cell>> map, std::vector<Platform> plt): 

		void loadFieldFromFile(std::string filename, std::fstream& stream);

		void play(); //starts game mode
		void sandBox(); //starts sandBox mode
	};
}