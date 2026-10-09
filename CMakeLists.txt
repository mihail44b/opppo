cmake_minimum_required(VERSION 4.4)

project(VehicleDepot LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)

add_executable(app
  main.cpp
  Vehicle.cpp
  Vehicle.hpp
  Depot.cpp
  Depot.hpp
)

target_compile_features(app PRIVATE cxx_std_20)
