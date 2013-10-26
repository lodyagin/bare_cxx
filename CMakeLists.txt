project(bare_c++lib CXX)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS 
  "-O2 -std=c++1y -Wall -nostdinc -nostdinc++")

add_subdirectory(lib)

include_directories(include)
link_directories(lib)

add_executable(hellocpp hellocpp.cpp)
target_link_libraries(hellocpp bare_c++lib)

