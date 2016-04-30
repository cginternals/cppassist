
# 
# External dependencies
# 

set(ADDITIONAL_LIBRARIES)
set(ADDITIONAL_INCLUDES)
if(NOT OPTION_BUILD_WITH_STD_REGEX)
    find_package(Boost COMPONENTS regex REQUIRED)
    
    if (Boost_FOUND)
        message(STATUS "Use Boost for regex.")
        
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} ${Boost_LIBRARIES})
        set(ADDITIONAL_INCLUDES ${ADDITIONAL_INCLUDES} ${Boost_INCLUDE_DIRS})
    else()
        message(WARNING "OPTION_BUILD_WITH_STD_REGEX is set to Off: Boost not found.")
        message(WARNING "Defaulting to C++11 regex.")
    endif()
endif()


# 
# Library name and options
# 

# Target name
set(target cppassist)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(feature_file "include/${target}/${target}_features.h")
set(export_file  "include/${target}/${target}_api.h")
set(export_macro "${target_upper}_API")


# 
# Sources
# 

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/io/readfile.h
    ${include_path}/io/directorytraversal.h
    ${include_path}/io/FilePath.h
    ${include_path}/io/SystemInfo.h

    ${include_path}/logging/AbstractLogHandler.h
    ${include_path}/logging/ConsoleLogHandler.h
    ${include_path}/logging/FileLogHandler.h
    ${include_path}/logging/LogMessage.h
    ${include_path}/logging/LogMessageBuilder.h
    ${include_path}/logging/LogMessageBuilder.hpp
    ${include_path}/logging/formatString.h
    ${include_path}/logging/formatString.hpp
    ${include_path}/logging/logging.h
    ${include_path}/logging/logging.hpp

    ${include_path}/strings/conversion.h
    ${include_path}/strings/conversion.hpp
    ${include_path}/strings/regex.h
    ${include_path}/strings/manipulation.h
    ${include_path}/strings/manipulation.hpp

    ${include_path}/threading/parallelfor.h
    ${include_path}/threading/parallelfor.hpp
)

set(sources
    ${source_path}/io/readfile.cpp
    ${source_path}/io/directorytraversal.cpp
    ${source_path}/io/FilePath.cpp
    ${source_path}/io/SystemInfo.cpp

    ${source_path}/logging/ConsoleLogHandler.cpp
    ${source_path}/logging/FileLogHandler.cpp
    ${source_path}/logging/LogMessage.cpp
    ${source_path}/logging/LogMessageBuilder.cpp
    ${source_path}/logging/formatString.cpp
    ${source_path}/logging/logging.cpp

    ${source_path}/strings/conversion.cpp
    ${source_path}/strings/regex.cpp
    ${source_path}/strings/manipulation.cpp

    ${source_path}/threading/parallelfor.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# 
# Create library
# 

# Build library
add_library(${target}
    ${sources}
    ${headers}
)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create API export header
generate_export_header(${target}
    EXPORT_FILE_NAME  ${export_file}
    EXPORT_MACRO_NAME ${export_macro}
)


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
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${ADDITIONAL_INCLUDES}

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${ADDITIONAL_LIBRARIES}

    PUBLIC
    ${DEFAULT_LIBRARIES}

    INTERFACE
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    $<$<BOOL:${OPTION_BUILD_WITH_STD_REGEX}>:USE_STD_REGEX>

    PUBLIC
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_upper}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

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
# Deployment
# 

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
