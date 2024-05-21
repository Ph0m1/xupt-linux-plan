cmake_minimum_required(VERSION 3.16)

project(qt VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
    menu.cpp
    menu.hpp
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
