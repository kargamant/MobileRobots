all:
	g++ --coverage -O0 -std=c++20 -o unit_tests testing.cpp ../Modules/ManageModule.cpp ../Modules/Gun.cpp ../Modules/EnergyGenerator.cpp ../Modules/Sensor.cpp ../Modules/Module.cpp ../Field/Field.cpp ../Field/Cell.cpp ../Interfaces/Platform.cpp ../Platforms/CommandCentre.cpp ../Platforms/MobilePlatform.cpp ../Platforms/RobotCommander.cpp ../Platforms/RobotDestroyer.cpp ../Platforms/KamikazeRobot.cpp ../Platforms/QuantumPlatform.cpp
	mv *.gcno gc_info
	mv *.gcda gc_info
