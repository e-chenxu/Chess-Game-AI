cmake_minimum_required(VERSION 3.5)
project(QtChess)

# Enable automatic Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the required Qt6 components
find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

# Add the source files
add_executable(QtChess src/gui/main.cpp)

# Link against Qt libraries
target_link_libraries(QtChess Qt6::Widgets Qt6::Core Qt6::Gui)

qt_add_resources(QtChess "resources.qrc")
