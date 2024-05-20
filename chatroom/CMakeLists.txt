cmake_minimum_required(VERSION 3.10)

project(chatroom)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(rapidjson REQUIRED)
add_subdirectory(src/code/cli)
add_subdirectory(src/code/json)
add_subdirectory(src/code/redis)
add_subdirectory(src/code/sever)

add_subdirectory(src/include)
add_subdirectory(src/lib)