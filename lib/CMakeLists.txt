include_directories(../include)
include_directories(${BARE_METAL_OS_SOURCE_DIR}/programs)

set(bare_c++lib_SOURCES
    csetjmp.s
    cstdlib.cpp
    iostream.cpp
    new.cpp
    start/atexit.cpp
    start/pure_virtual.cpp
)

add_library(bare_c++lib ${bare_c++lib_SOURCES})
