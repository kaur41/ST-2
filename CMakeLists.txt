cmake_minimum_required(VERSION 3.10.2)
project(ST-2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")

set(tool_dest "bin")
set(lib_dest "lib")
set(include_dest "include/")

# Отключаем pthread на Windows
if(WIN32)
    set(gtest_disable_pthreads ON)
    add_definitions(-DGTEST_HAS_PTHREAD=0)
endif()

# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(test)