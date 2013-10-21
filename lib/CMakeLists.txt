set(CMAKE_CXX_FLAGS 
  "-O2 -std=c++1y -Wall -nostdinc -nostdinc++")

include_directories(../include)

set(bare_c++lib_SOURCES
    iostream.cpp
)

add_library(bare_c++lib ${bare_c++lib_SOURCES})
