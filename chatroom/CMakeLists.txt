cmake_minimum_required(VERSION 3.10)

project(chatroom)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(rapidjson REQUIRED)
add_subdirectory(src)

include_directories(${CMAKE_SOURCE_DIR}/src/include)