cmake_minimum_required(VERSION 3.9)

add_subdirectory(./lib/googletest-master)
set(gtest_SOURCE_DIR, ./lib/googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp UtenzaTest.cpp dateTest.cpp datetimeTest.cpp transactionTest.cpp investmentTest.cpp contoFixture.cpp)
add_executable(unitTest ${TEST_SOURCE_FILES})
target_link_libraries(unitTest gtest gtest_main core)