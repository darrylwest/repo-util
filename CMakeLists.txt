#
# 2022-02-10 09:48:22 dpw
#
cmake_minimum_required(VERSION 3.30)
# todo: create header.in to read version
project(repos VERSION 1.0.1 LANGUAGES CXX)

# configure_file(app_version.hpp.in in app_version.hpp)

# to create a static (but much larger) binary
# set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)
add_compile_options(-Wall -Wextra -pedantic -Werror -O0)

# set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(${PROJECT_NAME} src/main.cpp) # should add new source files now...
target_include_directories(repos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

enable_testing()

# this compiles and adds build/tests/repo_unit_tests
add_subdirectory(test)

add_test(UnitTest test/repo_unit_tests)

# add_executable(${PROJECT_NAME} test/main-test.cpp) # should add new source files now...
# could define the file list this way, but not recommended
# file(GLOB_RECURSE SRC_FILES src/*.cpp)
# add_executable(repos ${SRC_FILES})

# could also add a library
# add_library(blah STATIC blah/Blah.cpp)
# add_subdirectory()
# @see this: https://www.youtube.com/watch?v=mKZ-i-UfGgQ

# find_package : will need this for OpenSSL, Compress, ssh etc.
# target_link_libraries(repos PUBLIC ${MY_LIB})
