cmake_minimum_required(VERSION 3.1)

project(Factorisation)

file(
GLOB_RECURSE
src_file
src/factorisation.c
src/consommateur.c
src/producteur.c
src/main.c
src/buffer.c
src/factorisation.h
src/consommateur.h
src/producteur.h
src/buffer.h
)

file(
GLOB
test_file
src/test_factorisation.c
src/factorisation.c
src/consommateur.c
src/producteur.c
src/buffer.c
src/factorisation.h
src/consommateur.h
src/producteur.h
src/buffer.h
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY obj)

#add_executable(factorisation ${src_file})

add_executable(factorisation ${src_file})

target_link_libraries(factorisation m)
target_link_libraries(factorisation pthread)
target_link_libraries(factorisation curl)

enable_testing()

add_executable(test_factorisation ${test_file})

target_link_libraries(test_factorisation cunit)
target_link_libraries(test_factorisation m)
target_link_libraries(test_factorisation pthread)
target_link_libraries(test_factorisation curl)
