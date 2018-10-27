# CMAKE template file. Easy use for small projects
# Date : 14/10/2018
#
# To use, put in a directory. Create subdirectories /src and /build
# cd build
# cmake ..
# make
# ./ConsoleTester

cmake_minimum_required (VERSION 3.10)

# Give the name of the project.
project (SuperSlots-Support)

# Detect if we are compiling on a 64 or 32 bit machine.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

# Use C++ 11
set (CMAKE_CXX_STANDARD 11)

# Create a ${HEADERS} and ${SOURCES} variables by looking recursively
# in the src/ folder.
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")


# Include the Libtech CMake project
set(LIBTECH_SUPPORT_OPENGL OFF CACHE BOOL "Build OpenGL Components")

add_subdirectory("lib/libtech")
include_directories("lib/libtech/include")

add_subdirectory("lib/pugixml")
include_directories("lib/pugixml/src")

# Set standard defines for Windows.
# TODO : Description of the definitions
IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

# Set standard defines for Linux. None needed :D
IF(UNIX)
ENDIF(UNIX)

# Setup the Static and Shared library builds
add_library(SUPERSLOTS-SUPPORT STATIC ${HEADERS} ${SOURCES})
add_library(SUPERSLOTS-SUPPORT_D SHARED ${HEADERS} ${SOURCES})

# Set the define to export the members
target_compile_definitions(SUPERSLOTS-SUPPORT PRIVATE SuperSlotsSupport_EXPORTS)
target_compile_definitions(SUPERSLOTS-SUPPORT_D PRIVATE SuperSlotsSupport_EXPORTS)

# Link dependencies
target_link_libraries(SUPERSLOTS-SUPPORT LIBTECH pugixml)
target_link_libraries(SUPERSLOTS-SUPPORT_D LIBTECH pugixml)

# Create the output executable, use the files found above.
add_executable(SlotsConsoleTester "src/main.cpp")
target_link_libraries(SlotsConsoleTester SUPERSLOTS-SUPPORT_D)

# Set special project properties
# On windows, set the debugging directory to the project directory, not the /build dir
# On linux, deactivate Wall (why?).
IF(WIN32)
    set_target_properties(SUPERSLOTS-SUPPORT PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
    set_target_properties(SUPERSLOTS-SUPPORT_D PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
    set_target_properties(SlotsConsoleTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
ELSEIF(UNIX)
    target_compile_options(SUPERSLOTS-SUPPORT PRIVATE -Wall)
    target_compile_options(SUPERSLOTS-SUPPORT_D PRIVATE -Wall)
    target_compile_options(SlotsConsoleTester PRIVATE -Wall)
ENDIF(WIN32)

# Copy the content files
add_custom_command(
    TARGET SUPERSLOTS-SUPPORT POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/content"
    $<TARGET_FILE_DIR:SUPERSLOTS-SUPPORT>/content
)
