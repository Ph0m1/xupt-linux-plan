cmake_minimum_required(VERSION 3.10)
project(cli)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(cli menu.cpp)

target_link_libraries(cli PRIVATE Qt5::Widgets nlohmann_json::nlohmann_json)
