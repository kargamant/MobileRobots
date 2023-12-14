cmake_minimum_required (VERSION 3.16)

project("MobileRobots")
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-fmax-errors=1 -g)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsfml-graphics -lsfml-window -lsfml-system")

add_subdirectory(Field)
add_subdirectory(Interfaces)
add_subdirectory(Modules)
add_subdirectory(Platforms)
add_subdirectory(Game)
add_subdirectory(MenueLib)
file(COPY resources DESTINATION .)

add_executable(main main.cpp Modules/ManageModule.cpp Game/sfml_main.cpp Game/Application.cpp)
find_package (SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(main Game Field Interfaces Modules Platforms Menue sfml-graphics sfml-window sfml-system sfml-audio)