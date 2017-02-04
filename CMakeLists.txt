project(bare_c++lib CXX ASM)

cmake_minimum_required(VERSION 2.8)

# TODO BareMetal OS sources search marco
#set(BARE_METAL_OS_SOURCE_DIR
#    /home/serg/Projects/BareMetal/src/BareMetal-OS
#>)

set(CMAKE_CXX_FLAGS 
  "-g -O0 -std=c++11 -m64 -Wall -nostdinc -nostdinc++ -nostdlib -fno-rtti")

add_definitions(-DBARE_CXX)

# The linux compilation is for debugging & testing
if(LINUX)
  add_definitions(-DLINUX)
  exec_program(
    ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crti.o
    OUTPUT_VARIABLE CRTI
  )
  exec_program(
    ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crtn.o
    OUTPUT_VARIABLE CRTN
  )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")
else()
  set(CRTI ${CMAKE_SOURCE_DIR}/lib/start/crti.s)
  set(CRTN ${CMAKE_SOURCE_DIR}/lib/start/crtn.s)
  set(CMAKE_EXE_LINKER_FLAGS 
      "-T ${CMAKE_SOURCE_DIR}/lib/start/app.ld ${CMAKE_EXE_LINKER_FLAGS}"
  )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
endif()

set(CRT0
    ${CMAKE_SOURCE_DIR}/lib/start/crt0.cpp
)

exec_program(
  ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crtbegin.o
  OUTPUT_VARIABLE CRTBEGIN
)
exec_program(
  ${CMAKE_CXX_COMPILER} ARGS -print-file-name=crtend.o
  OUTPUT_VARIABLE CRTEND
)
  
add_executable(hellocpp 
  ${CRT0} ${CRTI} ${CRTBEGIN}
  hellocpp.cpp
  ${CRTEND} ${CRTN}
)

add_subdirectory(lib)
add_subdirectory(tests)

include_directories(include)
#include_directories(${BARE_METAL_OS_SOURCE_DIR}/programs)
link_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(hellocpp bare_c++lib)

