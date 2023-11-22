# CMakeList.txt: проект CMake для MobileRobots; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project("MobileRobots")
set(CMAKE_CXX_STANDARD 20)
# Добавьте источник в исполняемый файл этого проекта.
# add_executable (MobileRobots "MobileRobots.cpp" "Field/Field.h" "Field/Cell.h" "Platforms/Platform.h" "Modules/Module.h" "Platforms/MobilePlatform.h" "RobotCommander.h" "Modules/ManageModule.h" "Platforms/CommandCentre.h" "Field/Obstacle.h" "Field/MovingObstacle.h" "Field/MassiveObstacle.h" "Field/PointOfInterest.h" "Modules/EnergyGenerator.h" "Modules/Sensor.h")
add_compile_options(-fmax-errors=1)
add_executable(main main.cpp Field/Field.cpp Field/Cell.cpp Interfaces/Platform.cpp "Interfaces/Moving.cpp" "Dialogue.h" "Platforms/CommandCentre.cpp" "Platforms/RobotCommander.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
