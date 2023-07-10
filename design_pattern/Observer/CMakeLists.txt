cmake_minimum_required(VERSION 3.11)

# set the project name
project(observ) 

# add the executable
add_executable(observ main.cpp Observer.hpp)

target_compile_options(observ PRIVATE -Wall -Wextra)
