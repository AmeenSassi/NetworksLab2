cmake_minimum_required(VERSION 3.7)
project(NetworksLab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Server/serverfunctions.cpp Server/Account.cpp)
add_executable(NetworksLab2 ${SOURCE_FILES})