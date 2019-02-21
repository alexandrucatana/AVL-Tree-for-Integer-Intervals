project(test_intervals_with_avl)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_REQUIRED_LIBRARIES $(CMAKE_REQUIRED_LIBRARIES) -lc++)

add_executable(test_intervals_with_avl  test_avl_merging_intervals.cpp )
target_link_libraries(test_intervals_with_avl catch_lib avl)
