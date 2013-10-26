project(bare_c++lib CXX)

cmake_minimum_required(VERSION 2.8)

# TODO BareMetal OS sources search marco
#set(BARE_METAL_OS_SOURCE_DIR
#    /home/serg/Projects/BareMetal/src/BareMetal-OS
#>)

set(CMAKE_CXX_FLAGS 
  "-O2 -std=c++11 -m64 -Wall -nostdinc -nostdinc++ -nostdlib -fno-rtti -fno-exceptions")

add_subdirectory(lib)

include_directories(include)
#include_directories(${BARE_METAL_OS_SOURCE_DIR}/programs)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(hellocpp hellocpp.cpp)
target_link_libraries(hellocpp bare_c++lib)

