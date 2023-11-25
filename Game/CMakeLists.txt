#add_link_options(-lsfml-graphics -lsfml-window -lsfml-system -lm)
add_library(Game Drawer.cpp)
#add_executable(MobileRobots ../Field/Field.cpp ../Field/Cell.cpp ../Interfaces/Platform.cpp ../Interfaces/Moving.cpp ../Interfaces/ ../Modules/Module.cpp ../CheckComponent.h Drawer.cpp)
#target_link_libraries(MobileRobots sfml-graphics sfml-window sfml-system)