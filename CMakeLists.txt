# CMAKE template file. Easy use for small projects
# Date : 14/10/2018
# 
# To use, put in a directory. Create subdirectories /src and /build
# cd build
# cmake ..
# make
# ./ConsoleTester 

cmake_minimum_required (VERSION 3.2)

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

# Create the output executable, use the files found above.
add_executable(ConsoleTester ${HEADERS} ${SOURCES})

# Set special project properties
# On windows, set the debugging directory to the project directory, not the /build dir
# On linux, deactivate Wall (why?).
IF(WIN32)
    set_target_properties(ConsoleTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
ELSEIF(UNIX)
    target_compile_options(ConsoleTester PRIVATE -Wall)
ENDIF(WIN32)
