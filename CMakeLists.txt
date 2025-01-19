cmake_minimum_required(VERSION 3.15)
project(QtExample)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QtExample ../src/gui/main.cpp)

target_link_libraries(QtExample Qt6::Widgets)
