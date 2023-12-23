#add_library(unit_tests testing.cpp)
#add_compile_options(--coverage)
#add_link_options(--coverage)
add_executable(unit_tests testing.cpp ../Modules/ManageModule.cpp ../Modules/Gun.cpp)
