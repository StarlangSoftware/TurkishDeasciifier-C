cmake_minimum_required(VERSION 3.23)
project(Deasciifier)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(morphological_analysis_c REQUIRED)
find_package(n_gram_c REQUIRED)

add_library(Deasciifier SimpleAsciifier.c SimpleAsciifier.h SimpleDeasciifier.c SimpleDeasciifier.h NGramDeasciifier.c NGramDeasciifier.h)
target_link_libraries(Deasciifier morphological_analysis_c::morphological_analysis_c n_gram_c::n_gram_c)
