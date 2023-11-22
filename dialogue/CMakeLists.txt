set(CMAKE_CXX_STANDARD 20)
add_library(dialogue "SignalManager.h" "DialogueSig.cpp" ../TernarySignal/TernarySignal.h ../TernarySignal/TernarySignal.cpp ../TernaryVector/TernaryVector.h ../TernaryVector/TernaryVector.cpp "Menue.cpp" "Menue.h" "DialogueVecDynamic.cpp")
