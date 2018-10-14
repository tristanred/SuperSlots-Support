cmake_minimum_required (VERSION 3.2)

project (SuperSlots-Support)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

set (CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")

IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

IF(UNIX)
ENDIF(UNIX)

add_executable(ConsoleTester ${HEADERS} ${SOURCES})

IF(WIN32)
    set_target_properties(ConsoleTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
ELSEIF(UNIX)
    target_compile_options(ConsoleTester PRIVATE -Wall)
ENDIF(WIN32)
