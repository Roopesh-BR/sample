cmake_minimum_required(VERSION 3.20.2)
set(CMAKE_CXX_STANDARD 17)

project(ExampleProject)

add_executable(aStarexe model.cpp pugixml.cpp route_model.cpp main.cpp render.cpp route_planner.cpp)