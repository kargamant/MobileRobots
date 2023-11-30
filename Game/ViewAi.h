#include "View.h"
#include "../ArtificialIntelligence.h"

namespace Game
{
	class ViewAi:public View
	{
	private:
		std::string formAiDescription();
	public:
		Robots::ArtificialIntelligence* ai;
		ViewAi(Robots::ArtificialIntelligence* ai, std::string texture_name, std::pair<int, int> position, std::string message, std::pair<int, int> txt_pos, sf::Vector2f scale = SPRITE_SCALE, std::string font_name = FONT_NAME, int character_size = CHARACTER_SIZE, sf::Color color = TEXT_COLOR) : ai(ai), View(texture_name, position, message, txt_pos, scale, font_name, character_size, color) {}

		void draw() override;
	};
}