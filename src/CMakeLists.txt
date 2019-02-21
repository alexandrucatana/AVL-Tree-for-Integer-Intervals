cmake_minimum_required (VERSION 3.12)
project (src)

message(${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)
set (CMAKE_REQUIRED_LIBRARIES $(CMAKE_REQUIRED_LIBRARIES) -lc++)


#include the subdirectory containing our source files
add_subdirectory (avl)
include_directories(${CMAKE_SOURCE_DIR}/avl)

add_executable (src main.cpp)

target_link_libraries (src avl)

install (TARGETS src DESTINATION bin)
