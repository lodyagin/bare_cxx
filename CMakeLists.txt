project(bare_c++lib CXX ASM)

cmake_minimum_required(VERSION 2.8)

# TODO BareMetal OS sources search marco
#set(BARE_METAL_OS_SOURCE_DIR
#    /home/serg/Projects/BareMetal/src/BareMetal-OS
#>)

# The linux compilation is for debugging & testing
if(LINUX)
  add_definitions(-DLINUX)
else()
  set(CMAKE_EXE_LINKER_FLAGS 
      "-T ${CMAKE_SOURCE_DIR}/lib/start/app.ld ${CMAKE_EXE_LINKER_FLAGS}"
  )
endif()

set(CMAKE_CXX_FLAGS 
  "-O2 -std=c++11 -m64 -Wall -nostdinc -nostdinc++ -nostdlib -fno-rtti -fno-exceptions")

add_subdirectory(lib)

include_directories(include)
#include_directories(${BARE_METAL_OS_SOURCE_DIR}/programs)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CRT0
    ${CMAKE_SOURCE_DIR}/lib/start/crt0.cpp
)

exec_program(
  ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crti.o
  OUTPUT_VARIABLE CRTI
)
exec_program(
  ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crtbegin.o
  OUTPUT_VARIABLE CRTBEGIN
)
exec_program(
  ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crtend.o
  OUTPUT_VARIABLE CRTEND
)
exec_program(
  ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crtn.o
  OUTPUT_VARIABLE CRTN
)
  
add_executable(hellocpp 
  ${CRT0} ${CRTI} ${CRTBEGIN}
  hellocpp.cpp
  ${CRTEND} ${CRTN}
)

target_link_libraries(hellocpp bare_c++lib)

