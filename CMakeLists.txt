#--------------------------------------------------------------------------------------------------
# \file  FindxLib.cmake
# \brief Find xLib
#
# XLIB_LOCATION    - root diractory [in]
# XLIB_FOUND       - found or not
# XLIB_DEFINITIONS - definitions
# XLIB_INCLUDES    - include pathes
# XLIB_SOURCES     - source pathes
# XLIB_LIBRARIES   - libraries list
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 2.6)

project(xLib)
set(PROJECT_TYPE "CXX")
set(CMAKE_BUILD_TYPE "RelWithDebInfo")

#--------------------------------------------------------------------------------------------------
# options
unset(xOPTION_NAMESPACE_XLIB      CACHE)
unset(xOPTION_DEBUG_DIALOG        CACHE)
unset(xOPTION_DEBUG_MODE_MSGBOX   CACHE)
unset(xOPTION_DEBUG_MODE_STDOUT   CACHE)
unset(xOPTION_DEBUG_MODE_LOG      CACHE)
unset(xOPTION_DEBUG_MODE_NO       CACHE)
unset(xOPTION_BUILD_MSG           CACHE)
unset(xOPTION_TESTS               CACHE)
unset(xOPTION_TEST_PRIVATE        CACHE)
unset(xOPTION_TEST_TRACING        CACHE)

option(xOPTION_NAMESPACE_XLIB      "Automatically include the xlib namespace" 1)
option(xOPTION_DEBUG_DIALOG        "Debug prompt dialog"                      1)
option(xOPTION_DEBUG_MODE_MSGBOX   "Debug mode: message box with plain text"  0)
option(xOPTION_DEBUG_MODE_STDOUT   "Debug mode: std::out with plain text"     1)
option(xOPTION_DEBUG_MODE_LOG      "Debug mode: logging with plain text"      0)
option(xOPTION_DEBUG_MODE_NO       "Debug mode: no debugging"                 0)
option(xOPTION_BUILD_MSG           "Build messages"                           0)
option(xOPTION_TESTS               "Use tests"                                1)
option(xOPTION_TEST_PRIVATE        "Test private data"                        1)
option(xOPTION_TEST_TRACING        "Use tracing in tests"                     1)

#--------------------------------------------------------------------------------------------------
# vars
unset(XLIB_FOUND       CACHE)
unset(XLIB_DEFINITIONS CACHE)
unset(XLIB_INCLUDES    CACHE)
unset(XLIB_SOURCES     CACHE)
unset(XLIB_LIBRARIES   CACHE)

unset(XLIB_LOCATION    CACHE)

if (NOT XLIB_LOCATION)
    set(XLIB_LOCATION ${CMAKE_SOURCE_DIR})
endif()

#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH ${XLIB_LOCATION}/CMake)
include(Configure)

#--------------------------------------------------------------------------------------------------
# includes, libs
set(XLIB_INCLUDES ${XLIB_INCLUDES} ${XLIB_LOCATION}/Include)
file(GLOB_RECURSE XLIB_SOURCES       ${XLIB_LOCATION}/Include/*.cpp)
file(GLOB_RECURSE XLIB_TESTS_SOURCES ${XLIB_LOCATION}/Tests/*.cpp)

#--------------------------------------------------------------------------------------------------
# definitions, libs, flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XLIB_DEFINITIONS}")

#-------------------------------------------------------------------------------
# dir "Tests"
include_directories(${XLIB_INCLUDES})
include_directories(${XLIB_LOCATION}/Tests/Include)

#--------------------------------------------------------------------------------------------------
# flags
include(CxxFlags)
# include(CMakeVariables)

#--------------------------------------------------------------------------------------------------
# libraries
set(XLIB_LIBRARIES ${XLIB_LIBRARIES} ${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS} pthread rt m z)

#--------------------------------------------------------------------------------------------------
# targets, install
add_executable(${PROJECT_NAME}_tests ${XLIB_SOURCES} ${XLIB_TESTS_SOURCES})
link_libraries(${XLIB_LIBRARIES})
