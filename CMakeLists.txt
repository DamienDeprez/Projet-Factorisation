cmake_minimum_required(VERSION 3.1)

project(Factorisation)

file(
GLOB_RECURSE
src_file
src/*
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY obj)

add_executable(
factorisation
${src_file}
)

target_link_libraries(factorisation m)

add_executable(
test_factorisation
src/test_factorisation.c
)

target_link_libraries(test_factorisation cunit)

