set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required (VERSION 3.8)

project ("lab2")
add_subdirectory("Tree")
add_subdirectory("NFA")
add_subdirectory("DFA")
add_subdirectory("MYREGEX")

#link_libraries(Tree)
#link_libraries(NFA)
#link_libraries(DFA)
link_libraries(MYREGEX)

add_executable(main Main.cpp "header.h")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()
