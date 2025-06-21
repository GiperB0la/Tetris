cmake_minimum_required(VERSION 3.16)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES
    Tetris/Main.cpp
    Tetris/src/*.cpp
)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Tetris ${SOURCES})

target_link_libraries(Tetris sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET Tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying Graphics"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:Tetris>/Graphics"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Tetris/Graphics"
            "$<TARGET_FILE_DIR:Tetris>/Graphics"
)