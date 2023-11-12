

namespace Robots
{
	class Moving
	{
	private:
		int velocity;
	public:
		Moving(int velocity) :this->velocity(velocity) {}

		int getVelocity() { return velocity; }
		Moving& setVelocity(int nvel) { velocity = nvel; retuirn* this; }

		void move(std::pair<int, int> vector)=0;
	};
}