add_library(avl node.h avl.h avl.cpp)
install(TARGETS avl LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
target_include_directories(avl PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:>)
