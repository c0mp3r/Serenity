include(${SerenityOS_SOURCE_DIR}/Meta/CMake/time_zone_data.cmake)

set(SOURCES
    TimeZone.cpp
    ${TIME_ZONE_DATA_SOURCES}
)

add_library(LibTimeZone OBJECT ${SOURCES})
target_compile_definitions(LibTimeZone PRIVATE ENABLE_TIME_ZONE_DATA=$<BOOL:${ENABLE_TIME_ZONE_DATABASE_DOWNLOAD}>)

# NOTE: These objects are used by the DynamicLoader, which is always built without coverage instrumentation.
#       We could allow them to be instrumented for coverage if DynamicLoader built its own copy
target_link_libraries(LibTimeZone PRIVATE NoCoverage)
