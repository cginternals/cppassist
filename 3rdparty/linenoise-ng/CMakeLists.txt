
#
# External dependencies
#


#
# Library name and options
#

# Target name
set(target linenoise-ng)

# Exit here if required dependencies are not met
message(STATUS "External ${target}")


#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/linenoise.h
    ${include_path}/ConvertUTF.h
)

set(sources
    ${source_path}/linenoise.cpp
    ${source_path}/ConvertUTF.cpp
    ${source_path}/wcwidth.cpp
)


#
# Create library
#

# Build library
add_library(${target} STATIC
    ${sources}
    ${headers}
)

# Create namespaced alias
add_library(externals::${target} ALIAS ${target})


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/source/include

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    INTERFACE
)


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LIBRARIES}

    INTERFACE
)


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE

    PUBLIC
    ${target_upper}_STATIC_DEFINE
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


#
# Compile options
#

target_compile_options(${target}
    PRIVATE

    PUBLIC
    # ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)


#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
)
