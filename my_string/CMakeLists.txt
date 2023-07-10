cmake_minimum_required(VERSION 3.11)

# set the project name
project(my_string) 

# add the executable
add_executable(my_string main.cpp my_string.cpp)

target_compile_options(my_string PRIVATE -Wall -Wextra)