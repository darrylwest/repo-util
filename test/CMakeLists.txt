#
# 2022-02-10 09:48:22 dpw
#
cmake_minimum_required(VERSION 3.16)

project(repo_unit_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)
find_package(Threads REQUIRED)
set(SOURCE_FILES main.cpp)

enable_testing()
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} fmt::fmt)


add_test(UnitTester ${PROJECT_NAME})

