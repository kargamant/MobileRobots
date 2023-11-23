cmake_minimum_required (VERSION 3.8)

project("MobileRobots")
set(CMAKE_CXX_STANDARD 20)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
add_compile_options(-fmax-errors=1)
#add_link_options(-lsfml-graphics -lsfml-window -lsfml-system -lm)
add_executable(MobileRobots ../Field/Field.cpp ../Field/Cell.cpp ../Interfaces/Platform.cpp "../Interfaces/Moving.cpp" "../Modules/Module.cpp" "../CheckComponent.h" "Drawer.cpp")
target_link_libraries(sfml-graphics sfml-window sfml-system)