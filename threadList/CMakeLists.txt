cmake_minimum_required(VERSION 3.11)

project(my_list) 

# add_executable(my_list main.cpp)
add_executable(my_list2 main2.cpp)

# target_compile_options(my_list PRIVATE -Wall -Wextra)
target_compile_options(my_list2 PRIVATE -Wall -Wextra)

target_link_libraries(my_list2 PUBLIC
pthread
)
