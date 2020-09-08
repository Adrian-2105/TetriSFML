cmake_minimum_required(VERSION 3.15)
project("Tetris-C++_SFML")

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SFML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib")
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

set (CMAKE_PROJECT_NAME )

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME} main.cpp src/Board.cpp include/Board.h src/Piece.cpp include/Piece.h src/Game.cpp include/Game.h src/Menu.cpp include/Menu.h)
target_link_libraries (${CMAKE_PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
