# CMakeList.txt: проект CMake для MobileRobots; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (MobileRobots "MobileRobots.cpp" "Field/Field.h" "Field/Cell.h" "Platforms/Platform.h" "Modules/Module.h" "Platforms/MobilePlatform.h" "RobotCommander.h" "Modules/ManageModule.h" "Platforms/CommandCentre.h" "Field/Obstacle.h" "Field/MovingObstacle.h" "Field/MassiveObstacle.h" "Field/PointOfInterest.h" "Modules/EnergyGenerator.h" "Modules/Sensor.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
