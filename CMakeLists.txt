cmake_minimum_required(VERSION 3.7)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MazeRecursiveBacktracker.cpp MazeRecursiveBacktracker.h)
add_executable(MazeSolver ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MazeSolver ${SFML_LIBRARIES})
endif()