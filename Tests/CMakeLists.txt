#--------------------------------------------------------------------------------------------------
# \file  CMakeList.txt
# \brief CMake file for build xLib tests
#--------------------------------------------------------------------------------------------------


cmake_minimum_required(VERSION 2.6)

project(xLib_test)

set(PROJECT_TYPE "CXX")
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    # None (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
    # Debug (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
    # Release (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
    # RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
    # MinSizeRel (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)

#--------------------------------------------------------------------------------------------------
# options
unset(xOPTION_TESTS        CACHE)
unset(xOPTION_TEST_PRIVATE CACHE)
unset(xOPTION_TEST_TRACING CACHE)

option(xOPTION_TESTS         "Use tests"            1)
option(xOPTION_TEST_PRIVATE  "Test private data"    1)
option(xOPTION_TEST_TRACING  "Use tracing in tests" 1)

# trace options
message("")
message("******************** Options *********************")
message("* xOPTION_TESTS:        ${xOPTION_TESTS}")
message("* xOPTION_TEST_PRIVATE: ${xOPTION_TEST_PRIVATE}")
message("* xOPTION_TEST_TRACING: ${xOPTION_TEST_TRACING}")
message("**************************************************")
message("")
#--------------------------------------------------------------------------------------------------
# modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
include(CMake/FindxLib.cmake)

#--------------------------------------------------------------------------------------------------
# definitions, libs, flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XLIB_DEFINITIONS}")

#--------------------------------------------------------------------------------------------------
# includes, libs
include_directories(${XLIB_INCLUDES})
include_directories(${CMAKE_SOURCE_DIR}/Tests/Include)
link_libraries(${XLIB_LIBRARIES})

#--------------------------------------------------------------------------------------------------
# sources
if (xOPTION_TESTS)
    file(GLOB_RECURSE xLib_tests_SOURCES "Tests/*.cpp")
else()
    file(GLOB_RECURSE xLib_tests_SOURCES "Tests/Test.cpp")
endif()

#--------------------------------------------------------------------------------------------------
# target
add_executable(${PROJECT_NAME} ${xLib_tests_SOURCES})
