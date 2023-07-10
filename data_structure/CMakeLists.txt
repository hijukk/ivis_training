cmake_minimum_required(VERSION 3.11)

project(my_list) 

add_executable(my_list main.cpp)

target_compile_options(my_list PRIVATE -Wall -Wextra)