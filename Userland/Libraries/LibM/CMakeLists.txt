set(SOURCES
    math.cpp
    ../LibC/ssp.cpp
)

set_source_files_properties (../LibC/ssp.cpp PROPERTIES COMPILE_FLAGS
    "-fno-stack-protector")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")
serenity_libc(LibM m)
