test:
	g++ -o sfml_test sfml_test.cpp -lsfml-graphics -lsfml-window -lsfml-system
release:
	g++ -std=c++20 -o MobileRobots sfml_test.cpp ../Field/Field.cpp ../Field/Cell.cpp ../Interfaces/Platform.cpp ../Interfaces/Moving.cpp ../Modules/Module.cpp ../CheckComponent.h ../Interfaces/Rulling.cpp ../Modules/Sensor.cpp Drawer.cpp ../Platforms/RobotCommander.cpp ../Platforms/CommandCentre.cpp ../Platforms/MobilePlatform.cpp ../Modules/EnergyGenerator.cpp ../Modules/ManageModule.cpp -lsfml-graphics -lsfml-window -lsfml-system
