cmake_minimum_required(VERSION 3.30)

project(game_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)

add_executable(game_engine src/main.cpp
        engine/src/Engine.cpp)

target_include_directories(game_engine PRIVATE
        engine/include
)

target_link_libraries(game_engine PRIVATE SDL3::SDL3)
