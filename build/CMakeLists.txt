cmake_minimum_required(VERSION 2.8)
project(MatrixTD)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(CMAKE_MODULE_PATH ../src/cmake)

find_package(SDL2 REQUIRED)
include_directories(../include ${SDL2_INCLUDE_DIR})

add_executable(MatrixTD ../src/driver.c ../src/MatrixTD.c)
target_link_libraries(MatrixTD ${SDL2_LIBRARIES} pthread SDL2)