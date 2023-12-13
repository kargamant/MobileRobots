#include "../Interfaces/Platform.h"
#include "../Platforms/MobilePlatform.h"
#include "../Interfaces/Destroying.h"
#include "../Modules/Gun.h"

namespace Robots
{
	class RobotDestroyer : public MobilePlatform, public Destroying
	{
	private:
		int gunInd;
		RobotDestroyer& setGunInd(int ngind) { gunInd = ngind; return *this; }
	public:
		RobotDestroyer(int max_radius = 1, int velocity = 0, std::string name="c3po", double energy = 0, int slots = 3, int cost = 0, std::pair<int, int> coordinates = std::pair<int, int>(0, 0));
		~RobotDestroyer()
		{
			delete &getGun();
		}

		int getGunInd() { return gunInd; }
		Gun& getGun() { return dynamic_cast<Gun&>(*robo[gunInd]); }

		void deleteModule(int ind) override;
		void deleteModule(Module* mod) override;
		void destroy(Field::Field* fld, std::pair<int, int> coordinates) override;

		//void turnOff(Module* mod) override;
	};
}