cmake_minimum_required(VERSION 3.16)
project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    Tetris/Main.cpp
    Tetris/src/Button.cpp
    Tetris/src/Tetris.cpp
)

include_directories(Tetris/include)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Tetris/Graphics
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Graphics
)