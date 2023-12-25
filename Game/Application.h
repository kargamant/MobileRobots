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
		Application(int width, int height) : field(width, height), ai(Robots::ArtificialIntelligence()) 
		{ 
			field.placeRandomPlatforms(2 + field.getWidth() / 4); 
			createGraph();
			connectGraph();
		}
		
		Robots::ArtificialIntelligence& getAi() { return ai; }
		Field::Field& getField() { return field; }
		void createGraph();
		void changeCellType(std::pair<int, int> coordinates, Field::CellType ntype)
		{
			field.changeCellType(coordinates, ntype);
			if (ntype == Field::CellType::obstacle)
			{
				ai.getGraph()[coordinates].isTraversable = false;
			}
			else if(ntype == Field::CellType::ground)
			{
				ai.getGraph()[coordinates].isTraversable = true;
			}
		}

		void loadFieldFromFile(std::string filename, std::fstream& stream);

		void play(bool windowView=true); //starts game mode
		void play_parallel();
		void sandBox(); //starts sandBox mode
		void connectGraph();
		void updateGraphTraversity();
	};
}