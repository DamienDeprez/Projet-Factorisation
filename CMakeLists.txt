cmake_minimum_required(VERSION 3.1)

project(Factorisation)

file(
GLOB_RECURSE
src_file
src/*
)

file(
GLOB
test_file
src/test_factorisation.c src/factorisation.c
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY obj)

#add_executable(factorisation ${src_file})

add_executable(factorisation ${src_file})

target_link_libraries(factorisation m)

enable_testing()

add_executable(test_factorisation ${test_file})

target_link_libraries(test_factorisation cunit)
target_link_libraries(test_factorisation m)
