cmake_minimum_required(VERSION 3.1)

project(Factorisation)

file(
GLOB_RECURSE
src_file
src/main/*
)

file(
GLOB_RECURSE
test_file
src/test/*
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY obj)

add_executable(
factorisation
${src_file}
)

target_link_libraries(factorisation m)

enable_testing()

add_executable(
test_factorisation
${test_file}
)

target_link_libraries(test_factorisation cunit)
