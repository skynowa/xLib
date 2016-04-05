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


#--------------------------------------------------------------------------------------------------
# options
option(xOPTION_PROJECT_HEADER_ONLY   OFF CACHE BOOL "Project: header only"              0)
option(xOPTION_PROJECT_LIB_STATIC    OFF CACHE BOOL "Project: static library"           1)
option(xOPTION_PROJECT_LIB_SHARE     OFF CACHE BOOL "Project: share library"            0)
option(xOPTION_PROJECT_LIB_MODULE    OFF CACHE BOOL "Project: dynamic-link library"     0)

if (NOT DEFINED xOPTION_BUILD_TESTS)
    option(xOPTION_BUILD_TESTS OFF CACHE BOOL "Build tests" 1)
endif()

option(xOPTION_CPP11                 OFF CACHE BOOL "Support C++11 language"            0)
option(xOPTION_DEBUG_DIALOG          OFF CACHE BOOL "Debug prompt dialog"               0)
option(xOPTION_DEBUG_MODE_MSGBOX     OFF CACHE BOOL "Debug mode: message box"           0)
option(xOPTION_DEBUG_MODE_STDOUT     OFF CACHE BOOL "Debug mode: std::cout"             0)
option(xOPTION_DEBUG_MODE_LOG        OFF CACHE BOOL "Debug mode: logging"               0)
option(xOPTION_DEBUG_MODE_STDOUT_LOG OFF CACHE BOOL "Debug mode: std::cout and logging" 0)
option(xOPTION_DEBUG_MODE_EXCEPTION  OFF CACHE BOOL "Debug mode: exception"             1)
option(xOPTION_DEBUG_MODE_NO         OFF CACHE BOOL "Debug mode: no debugging"          0)
option(xOPTION_BUILD_MSG             OFF CACHE BOOL "Build messages"                    0)
option(xOPTION_TEST_PRIVATE          OFF CACHE BOOL "Test private data"                 0)
option(xOPTION_TEST_TRACING          OFF CACHE BOOL "Use tracing in tests"              1)


message("")
message(STATUS "xOPTION_PROJECT_HEADER_ONLY   : ${xOPTION_PROJECT_HEADER_ONLY}")
message(STATUS "xOPTION_PROJECT_LIB_STATIC    : ${xOPTION_PROJECT_LIB_STATIC}")
message(STATUS "xOPTION_PROJECT_LIB_SHARE     : ${xOPTION_PROJECT_LIB_SHARE}")
message(STATUS "xOPTION_PROJECT_LIB_MODULE    : ${xOPTION_PROJECT_LIB_MODULE}")
message(STATUS "xOPTION_BUILD_TESTS           : ${xOPTION_BUILD_TESTS}")
message("")
# message(STATUS "xOPTION_CPP11                 : ${xOPTION_CPP11}")
# message(STATUS "xOPTION_DEBUG_DIALOG          : ${xOPTION_DEBUG_DIALOG}")
# message(STATUS "xOPTION_DEBUG_MODE_MSGBOX     : ${xOPTION_DEBUG_MODE_MSGBOX}")
# message(STATUS "xOPTION_DEBUG_MODE_STDOUT     : ${xOPTION_DEBUG_MODE_STDOUT}")
# message(STATUS "xOPTION_DEBUG_MODE_LOG        : ${xOPTION_DEBUG_MODE_LOG}")
# message(STATUS "xOPTION_DEBUG_MODE_STDOUT_LOG : ${xOPTION_DEBUG_MODE_STDOUT_LOG}")
# message(STATUS "xOPTION_DEBUG_MODE_EXCEPTION  : ${xOPTION_DEBUG_MODE_EXCEPTION}")
# message(STATUS "xOPTION_DEBUG_MODE_NO         : ${xOPTION_DEBUG_MODE_NO}")
# message(STATUS "xOPTION_BUILD_MSG             : ${xOPTION_BUILD_MSG}")
# message(STATUS "xOPTION_TEST_PRIVATE          : ${xOPTION_TEST_PRIVATE}")
# message(STATUS "xOPTION_TEST_TRACING          : ${xOPTION_TEST_TRACING}")
# message("")
#--------------------------------------------------------------------------------------------------
