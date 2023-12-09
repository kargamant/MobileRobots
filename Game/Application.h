#include "../Field/Field.h"
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
		Application(Field::Field& fld, Robots::ArtificialIntelligence& ai) : field(fld), ai(ai) { createGraph(); }
		Application() : field(Field::Field()), ai(Robots::ArtificialIntelligence()) { createGraph(); } //in this case Field will be totally random
		Application(int width, int height) : field(width, height), ai(Robots::ArtificialIntelligence()) {  createGraph(); } //field.placeRandomPlatforms(1 + field.getWidth() / 4);
		
		Robots::ArtificialIntelligence& getAi() { return ai; }
		Field::Field& getField() { return field; }
		void createGraph();

		void loadFieldFromFile(std::string filename, std::fstream& stream);

		void play(); //starts game mode
		void sandBox(); //starts sandBox mode
	};
}