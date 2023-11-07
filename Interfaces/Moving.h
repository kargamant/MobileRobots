

namespace Robots
{
	class Moving
	{
	private:
		int velocity;
	public:
		void move(std::pair<int, int> vector)=0;
	};
}