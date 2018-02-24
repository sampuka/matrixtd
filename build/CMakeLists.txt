cmake_minimum_required(VERSION 2.8)
project(MatrixTD)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c99 -g")

set(CMAKE_MODULE_PATH ../src/cmake)

find_package(SDL2 REQUIRED)
include_directories(../include ${SDL2_INCLUDE_DIR})

#add_executable(sdltest ../src/sdltest.c)
add_executable(MatrixTD ../src/driver.c ../src/MatrixTD.c ../src/MatrixTDMap.c)
#target_link_libraries(sdltest SDL2)
target_link_libraries(MatrixTD ${SDL2_LIBRARIES} pthread SDL2)