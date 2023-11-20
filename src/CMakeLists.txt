cmake_minimum_required(VERSION 3.23)
project(Deasciifier C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(Deasciifier src/SimpleAsciifier.c src/SimpleAsciifier.h src/SimpleDeasciifier.c src/SimpleDeasciifier.h src/NGramDeasciifier.c src/NGramDeasciifier.h)
target_link_libraries(Deasciifier ${CONAN_LIBS})
