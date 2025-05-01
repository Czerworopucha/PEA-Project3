cmake_minimum_required(VERSION 3.25)
project(pea_projekt_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(pea_projekt_3 main.cpp matrix.cpp matrix.h geneticAlgorithm.cpp geneticAlgorithm.h specimen.cpp specimen.h)
