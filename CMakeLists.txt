cmake_minimum_required(VERSION 3.8)
project(untitled24)

set(CMAKE_CXX_STANDARD 17)
#add_subdirectory(lib/googletest)
#add_subdirectory(lib/googlemock)
 include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


 add_executable(testtar test.cpp typed_test.cpp typed_test.h simple_test.cpp test_F.cpp queue.h prime_table.h type_P.cpp test_P2.cpp TEST_P3.cpp)
 target_link_libraries(testtar gtest gtest_main)

